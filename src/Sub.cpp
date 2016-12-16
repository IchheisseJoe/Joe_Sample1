#include "ros/ros.h"
#include "actionlib_msgs/GoalID.h"
#include "std_msgs/String.h"
#include <iostream>
#include <stdlib.h>


using namespace std;

ros::Subscriber RobotUtillSub;
ros::Publisher	CancelGoalPub;

void CancelGoal()
{
	actionlib_msgs::GoalID cancel_goal;
	if(ros::ok())
	{
		CancelGoalPub.publish(cancel_goal);
	}
}

void SubscriberCallback(const std_msgs::String::ConstPtr& msg)
{
	//cout<< msg->data << endl;
	int nCmd=atoi(msg->data.c_str());
	switch (nCmd)
	{
		case 1:
			cout<<"Change to SLAM mode"<<endl;
			//	TODO
			break;
		case 2:
			cout<<"Change to Navigation mode"<<endl;
			//	TODO
			break;
		case 3:
			cout<<"reboot robot system"<<endl;
			system("sync;sync;echo kikison1 | sudo -S reboot");
			break;
		case 4:
			cout<<"shutdown robot system"<<endl;
			system("sync;sync;echo kikison1 | sudo -S shutdown -P now");
			break;
		case 5:
			cout<<"publish cancel goal"<<endl;
			CancelGoal();
			break;
		default:
			ROS_ERROR("Invalid string %s", msg->data.c_str());
	}
	
}
	
int main(int argc, char* argv[])
{
	ros::init(argc, argv, "robot_utility");
	ros::NodeHandle nh1, nh2;
	if(nh1.hasParam("param_test"))
	{	
		string strParam;
		nh1.getParam("param_test", strParam);
		cout<<"getParam return string : "<<strParam<<endl;
	}
	else
	{
		ROS_ERROR("parameter \"param_test\" not found");
	}
	
	RobotUtillSub=nh1.subscribe("robot_utilities", 1024, SubscriberCallback);
	CancelGoalPub=nh2.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 1024);
	ros::spin();
	return 0;
}
