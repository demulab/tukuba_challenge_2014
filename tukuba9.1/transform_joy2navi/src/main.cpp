#include<iostream>
#include"ros/ros.h"
#include<geometry_msgs/Twist.h>
#include <sensor_msgs/Joy.h>

using namespace std;

//指令値
double nav_x = 0.0;
double nav_theta = 0.0;

//ジョイスティックからの指令を受信
void joyCallback(const sensor_msgs::Joy::ConstPtr& msg);

int main(int argc, char **argv)
{
	//ROSの準備
	ros::init(argc, argv, "joy_subscribe");

	ros::NodeHandle n;

	geometry_msgs::Twist navi;
	
	ros::Subscriber joy_msg = n.subscribe("/joy", 100, joyCallback);
	ros::Publisher pub_navi = n.advertise<geometry_msgs::Twist>("cmd_vel", 100);
	
	while(ros::ok())
	{
		usleep(1000*100);
		
		pub_navi.publish(navi);
		ros::spinOnce();
		navi.linear.y = 0.0;
		navi.linear.x = nav_x;
		navi.angular.z = -nav_theta;
	}
	return 0;
}


void joyCallback(const sensor_msgs::Joy::ConstPtr& msg)
{
	if((msg->axes[1] || msg->axes[2])&&(msg->buttons[10])){ 
		nav_x = msg->axes[1];
		nav_theta = -msg->axes[2];
	}
	else
	{
		nav_x = 0;
		nav_theta = 0;
	}
}



