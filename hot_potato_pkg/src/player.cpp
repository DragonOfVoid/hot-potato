#include "ros/ros.h"
#include "hot_potato_pkg/ballInfo.h"
#include <sstream>

#define PLAYERS 10;

using namespace ros;
Publisher pub;
int n, count=1;
bool ln=false;
bool mem[10];


void playerCallback(const hot_potato_pkg::ballInfo::ConstPtr &msg)
{
	Rate rate(1);

	if(n==msg->player)
	{
		if(count>=10 )
		{
			ROS_INFO("player %d won!",n);
		}
		else
		{
			ln=true;
			ROS_INFO("Player %d, got it!", msg->player);
			hot_potato_pkg::ballInfo msgN;
				if(msg->time2exp<=0)
				{
					ROS_INFO("Player %d out!", msg->player);
					msgN.time2exp=1000;
				}
				else
				{
					msgN.time2exp=msg->time2exp;
				}

				int a;

				do
				{
					a= rand()%10+1;
				}while(a==n | mem[a-1]==true);

				msgN.player = a;
				rate.sleep();
				ROS_INFO("Passing it to player %d", a);
				pub.publish(msgN);
				ln=false;

		}
	}

	if(msg->time2exp<=0)
	{
		mem[msg->player-1]=true;
		count++;
	}

}


int main (int argc, char **argv)
{
	n = atoi(argv[1]);
	init(argc, argv, "player");
	
	for(int i=0; i<10; i++)
		mem[i]=false;

	NodeHandle node;
	pub = node.advertise<hot_potato_pkg::ballInfo>("fromPlayers", 1000);
	Subscriber sub = node.subscribe("toPlayers", 1000, playerCallback);
	

	spin();
	return 0;
}
