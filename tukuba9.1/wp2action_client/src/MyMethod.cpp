#include"MyMethod.h"

double changeTheta(double theta)
{
    double returnTheta=theta;
    if (theta > M_PI)  {  returnTheta = theta - 2.0 * M_PI;    }
    if (theta < -M_PI)  {  returnTheta = theta + 2.0 * M_PI;    }
    return returnTheta;
}

double gettimeofday_sec()
{
     struct timeval tv; gettimeofday(&tv, NULL);
     return tv.tv_sec + tv.tv_usec * 1e-6;
}

int roundOff(double x)
{
    if(x-(int)x < 0.5)
    {   return (int)x;  }
    else
    {   return (int)x+1;  }
}

double randGaussian(double standard, double statndardDeviation)
{
    //ボックス・ミュラー法
    double r1 = (double)rand()/(double)RAND_MAX;
    double r2 = (double)rand()/(double)RAND_MAX;
    if(fabs(r1) <= 0.0001)
    {   return 0;   }
    if(fabs(r2) <= 0.0001)
    {   return 0;   }
    return statndardDeviation *( sqrt(-2.0*log(r1))*cos(2.0*M_PI*r2)) +standard;
}

double gaussian(double x, double y, double statndardDeviation)
{
    return exp(-(pow(x,2.0)+pow(y,2.0))/(2.0*pow(statndardDeviation, 2.0)));
}

//最小２乗法から近似直線を得る
// *data : 入力データ
// dataNum : 入力データ数
// *a : 傾き
// *b : 切片
// *c : x = c(定数)などx軸に垂直な場合、x軸と交わる点を返す。
bool leastSquaresMethod(point *data, int dataNum, double *a, double *b, double *c)
{
	double sumX=0.0;
	double sumY=0.0;
	double sumXY=0.0;
	double sumXX=0.0;
	
	//xの値が全て同じ場合nanになる。これを防止するためのフラグ
	bool errorFlag=true;
	for(int i=0; i<dataNum; i++)
	{
		if(data[0].x != data[i].x)
		{
			errorFlag=false;
			break;
		}
	}
	if(errorFlag)
	{
		*a = 0.0;	
		*b = 0.0;	
		*c = data[0].x;
		return false;
	}

	for(int i=0; i<dataNum; i++)
	{
		sumX += data[i].x;
		sumY += data[i].y;
		sumXY += data[i].x*data[i].y;
		sumXX += pow(data[i].x, 2.0);
	}
	//傾き
	*a = (dataNum*sumXY - sumX*sumY)/(dataNum*sumXX - pow(sumX, 2.0));
	//切片
	*b = (sumXX*sumY - sumXY*sumX)/(dataNum*sumXX - pow(sumX, 2.0));
	//エラー処理用
	*c = 0.0;
	return true;
}
