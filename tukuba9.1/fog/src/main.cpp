#include<iostream>
#include"Fog.hpp"
#include"My_method.hpp"
#include"MyDefine.h"

#include"ros/ros.h"

#define PORT_NAME_FOG "/dev/ttyUSB0"
//#define PORT_NAME_FOG "/dev/ttyUSB2"
//#define PORT_NAME_FOG "/dev/serial/by-path/pci-0000:00:1d.0-usb-0:1.2.4:1.0-port0"

int main(int argc, char **argv)
{
	ros::init(argc, argv, "fog_server");	//ROSの初期化

	std::string port_device; 

	//ノードハンドルの宣言
	ros::NodeHandle n;				
	ros::NodeHandle private_nh("~");

	if(!private_nh.getParam("port_device", port_device))
		port_device = PORT_NAME_FOG;

	FogClass fog(port_device);
	
	//サービスの登録
	ros::ServiceServer service = n.advertiseService("FOG", &FogClass::receiveFOGdata, &fog);
	ROS_INFO("Ready to FOG");

	ros::spin();

	return 0;
}
