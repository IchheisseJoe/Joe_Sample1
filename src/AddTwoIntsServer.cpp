#include "ros/ros.h"
#include "Joe_Sample1/AddTwoInts.h"

bool add(Joe_Sample1::AddTwoInts::Request  &req,
         Joe_Sample1::AddTwoInts::Response &res)
{
	res.sum = req.a + req.b;
	ROS_INFO("request: x=%ld, y=%ld", (long int)req.a, (long int)req.b);
	ROS_INFO("sending back response: [%ld]", (long int)res.sum);
	return true;
}

int main(int argc, char **argv)
{
	ros::init(argc, argv, "AddTwoIntsServer");
	ros::NodeHandle n;

	ros::ServiceServer service = n.advertiseService("add_two_ints", add);
	ROS_INFO("Ready to add two ints.");
	ros::spin();

	return 0;
}
