
#ifndef _FOG_H_
#define _FOG_H_

#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <iostream>
#include <termios.h>

#include "My_method.hpp"
#include "Serial.hpp"

//ROSのヘッダーファイル
#include"ros/ros.h"
#include"fog/FOG.h"

#define RATE_OFFSET 5 //sec
#define RESPONSE_MAX_SIZE 7
#define SEND_MAX_SIZE 7

//FOGクラス
class FogClass
{
private:
	Serial serial;
	unsigned char send_data[SEND_MAX_SIZE];
	int send_size;
	unsigned char response_data[RESPONSE_MAX_SIZE];
	int response_size;
	double FOG_angle;

public:	
	FogClass(std::string port_device);
    ~FogClass();
	void GetAngleCommand();
	void GetAngle();
    void ClearCommand();
	void OffsetCommand();
	void IntegralCommand();
	
	//コールバックの宣言(ROS)
	bool receiveFOGdata(fog::FOG::Request&req, fog::FOG::Response&res);
};

#endif
