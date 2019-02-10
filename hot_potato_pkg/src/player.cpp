#include "ros/ros.h"
#include "std_msgs/String.h"
#include <sstream>

using namespace ros;
Publisher pub;
Subscriber sub;
int n;

void playerCallback(const std_msgs::String::ConstPtr &msg)
{
	Rate rate(1);
	if(n==atoi(msg->data.c_str()))
	{
		ROS_INFO("Player %s, got it!", msg->data.c_str());
		std_msgs::String msgN;
		std::stringstream ss;
		ss << rand()%10+1;
		msgN.data = ss.str();
		rate.sleep();
		ROS_INFO("Passing it to player %s", msgN.data.c_str());
		pub.publish(msgN); 
	}	
}



int main (int argc, char **argv)
{
	n = atoi(argv[1]);
	init(argc, argv, "player");
	
	NodeHandle node;
	pub = node.advertise<std_msgs::String>("fromPlayers", 1000);
	sub = node.subscribe("toPlayers", 1000, playerCallback);
	
	spin();
	return 0;
}
