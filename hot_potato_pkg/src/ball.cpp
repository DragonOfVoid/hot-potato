#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

using namespace ros;
Publisher pub;
Subscriber sub;

void ballCallback(const std_msgs::String::ConstPtr  &msg)
{
	Rate rate(2);
	rate.sleep();
	ROS_INFO("flying to player %s", msg->data.c_str());
	rate.sleep();
	pub.publish(msg); 
	
}



int main (int argc, char **argv)
{
	init(argc, argv, "ball");
	
	NodeHandle node;
	pub = node.advertise<std_msgs::String>("toPlayers", 1000);
	sub = node.subscribe("fromPlayers", 1000, ballCallback);
	spin();
	return 0;
}
