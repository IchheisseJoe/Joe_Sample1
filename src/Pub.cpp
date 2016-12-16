#include "ros/ros.h"
#include "std_msgs/String.h"
#include "actionlib_msgs/GoalID.h"
#include <string>
#include <sstream>

using namespace std;

int main(int argc, char* argv[])
{
	ros::init(argc, argv, "cancel_goal");
	
	ros::NodeHandle	nh;
	ros::Publisher	CancelGoalPub=nh.advertise<actionlib_msgs::GoalID>("/move_base/cancel", 1024);
	ros::Rate 		LoopRate(1);
	
	while(ros::ok())
	{
		actionlib_msgs::GoalID data;
		CancelGoalPub.publish(data);
		ros::spinOnce();
		LoopRate.sleep();
	}

	return 0;
}

