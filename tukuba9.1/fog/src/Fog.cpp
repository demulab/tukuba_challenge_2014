#include "Fog.hpp"
//シリアル通信の設定(FOG用)
//#define PORT_NAME_FOG "/dev/ttyUSB1"	//ポート名(mainへ)
#define BAUD_RATE_FOG B9600			//通信速度
#define DATA_BIT_FOG CS8			//データビット
#define STOP_BIT_FOG 0				//ストップビット ※:補足「0なら1、 CSTOBなら2」
#define PARITY_FOG PARENB		//パリティ※ 補足「奇数にしたい場合は |PARODD を加える　」

//FOGへの命令一覧
#define CLEAR 0
#define INTEGRAL 1
#define OFFSET 2
#define GET_ANGLE 3

using namespace std;

FogClass::FogClass(std::string port_device)
{
//	serial.init(PORT_NAME_FOG, BAUD_RATE_FOG, DATA_BIT_FOG, STOP_BIT_FOG, PARITY_FOG);
	serial.init(port_device.c_str(), BAUD_RATE_FOG, DATA_BIT_FOG, STOP_BIT_FOG, PARITY_FOG);

	memset(send_data, 0, SEND_MAX_SIZE);
	memset(response_data, 0, RESPONSE_MAX_SIZE);
}

FogClass::~FogClass()
{

}
//シリアル通信を用いてFOGの値を受け取る
bool FogClass::receiveFOGdata(fog::FOG::Request&req, fog::FOG::Response&res)
{
	if(req.order == CLEAR)
	{	ClearCommand();	}
	else if(req.order == INTEGRAL)
	{	IntegralCommand();	}
	else if(req.order == OFFSET)
	{	OffsetCommand();	}
	else if(req.order == GET_ANGLE)
	{	GetAngleCommand();	}
	else
	{	
		ROS_INFO("ERROR_COMMAND!! -FOG-");
		res.response_header = 0;
		res.theta = 0;
		return false;
	}
	
	//シリアル送信(FOG)
	serial.send_sci(send_data, send_size);
	//シリアル受信(FOG)
	unsigned char header = 0;
	if(response_size > 1)
	{	header = 0x02;	}
	if(response_size == 1)
	{	header = 0x06;	}
	serial.receive_sci(response_data, response_size, &header, 1);
	res.response_header = (int)response_data[0];
	if(response_data[0] == 0x02)
	{
		GetAngle();
		res.theta = FOG_angle; 
	}
	else
	{	
		res.theta = 0;
	}

	return true;
}

//FOGの角度を0degにリセットするためのデータを作成
void FogClass::ClearCommand()
{
	ROS_INFO("CLEAR");
	send_data[0] = 0x02;
	send_data[1] = 0x43;
	send_data[2] = 0x03;
	send_data[3] = send_data[1]+send_data[2];	
	send_size = 4;
	response_size = 1;
}

//FOGのレート(角速度)のオフセットを指定秒数間測定し、測定オフセットを差し引いた形でレートを出力する。
//指定時間0～255[sec]
void FogClass::OffsetCommand()
{
	ROS_INFO("OFFSET");
	send_data[0] = 0x02;
	send_data[1] = 0x4F;
	unsigned char rate_offset[2] = {0};
	ChangeFigure(RATE_OFFSET / 16, &rate_offset[0]);
	ChangeFigure(RATE_OFFSET % 16, &rate_offset[1]);
	send_data[2] = rate_offset[0];
	send_data[3] = rate_offset[1];
	send_data[4] = 0x03;
	send_data[5] = send_data[1]+send_data[2]+send_data[3]+send_data[4] ;	
	send_size = 6;
	response_size = 1;
}

//FOGの内部で積分を開始または停止させるためのデータを作成
void FogClass::IntegralCommand()
{
	ROS_INFO("INTEGRAL");
	send_data[0] = 0x02;
	send_data[1] = 0x53;
	send_data[2] = 0x03;
	send_data[3] = send_data[1]+send_data[2];	
	send_size = 4;
	response_size = 1;
}

//FOGからデータを受信するためのデータを作成
void FogClass::GetAngleCommand()
{
	send_data[0] = 0x02;
	send_data[1] = 0x41;
	send_data[2] = 0x03;
	send_data[3] = send_data[1]+send_data[2];	
	send_size = 4;
	response_size = 7;
}

//FOGから受信したデータを元に角度(rad)を算出
void FogClass::GetAngle()
{
	double angle_dummy;
	int r_data[4] = {0};
	
	static char last_response_data[4] = {0};
	if((isnan(response_data[0]) == false)&&(isnan(response_data[1]) == false)&&(isnan(response_data[2]) == false)&&(isnan(response_data[3]) == false)&&
		(isinf(response_data[0]) == false)&&(isinf(response_data[1]) == false)&&(isinf(response_data[2]) == false)&&(isinf(response_data[3]) == false))
	{
		for(int i=0; i<4; i++)
		{
			last_response_data[i] = response_data[i];
		}
	}
	else
	{
		for(int i=0; i<4; i++)
		{
			response_data[i] = last_response_data[i];
		}
	}

	for(int i=0; i<4; i++)
	{
		ChangeCharacter(&r_data[i] ,response_data[i+1]);	
	}
	

	angle_dummy = 0.0055 * (((double)r_data[0] * 16.0 * 16.0 * 16.0) + ((double)r_data[1] * 16.0 * 16.0) + ((double)r_data[2] * 16.0) + (double)r_data[3]);

	if (angle_dummy > 360.0)
	{	return;	}
	else if (angle_dummy <	0.0)
	{	return;	}
	
	
#ifdef OUTLIER
    // 過去データN個(簡単のため奇数）の中央値を求め、現在値が中央値よりある値以上大きいと外れ値とする
    // 挿入ソート
    const int num = 11;
    const int outlier = 10; // 10°外れ値の閾値
    static double fog_array[num];
    static int array_count = 0;
    double median, diff; // 中央値、差

	fog_array[array_count++] = angle_dummy;

	if (array_count == num) {
		array_count = 0;
	}
	insertion(fog_array, num); // 挿入ソート
	median = fog_array[(int) num/2];
	diff = fabs(median - angle_dummy);
	
	if (diff > outlier)
	{	return;	}
	
#endif
	angle_dummy = angle_dummy * DEG2RAD;
	FOG_angle = changeAngle(angle_dummy);
	//ROSの座標系に合わせるために符号反転
	FOG_angle = -FOG_angle;
}


