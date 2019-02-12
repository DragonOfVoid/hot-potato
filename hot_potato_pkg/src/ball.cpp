#include "ros/ros.h"
#include "hot_potato_pkg/ballInfo.h"
#include <sstream>

using namespace ros;
Publisher pub, pub2;
Subscriber sub;

void ballCallback(const hot_potato_pkg::ballInfo::ConstPtr  &msg)
{
	Rate rate(2);
	hot_potato_pkg::ballInfo msgN;
	msgN.player = msg->player;
	msgN.time2exp = msg->time2exp-rand()%500;
	rate.sleep();
	ROS_INFO("flying to player %d", msg->player);
	rate.sleep();
	pub.publish(msgN);
	
}



int main (int argc, char **argv)
{
	init(argc, argv, "ball");
	
	NodeHandle node;
	pub = node.advertise<hot_potato_pkg::ballInfo>("toPlayers", 1000);

	sub = node.subscribe("fromPlayers", 1000, ballCallback);

	spin();


	return 0;
}
