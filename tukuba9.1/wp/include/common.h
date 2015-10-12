/*** WayPoint Maker 2011 http://demura.net ***/

//! 共通ヘッダファイル
/*! 共通に使われる定数や構造体など

 \file   common.h
 \author Kosei Demura
 \date   2010-09-07
*/

#ifndef _COMMON_H_
#define _COMMON_H_

#ifndef M_PI
#define M_PI (double) 3.1415926535897932384626433832795029
#endif

#define DEG_TO_RAD  (M_PI/180.0)
#define RAD_TO_DEG  (180.0/M_PI)


#define NUM 4            // Number of wheels
#define STEP_SIZE 0.02   // step size for dWorldStep

#include "MyDefine.h"


typedef struct
{
    double latitude;   //!< [deg]
    double longitude;  //!< [deg]
    double x;        //!< [m]
    double y;        //!< [m]
    double offset;   //!< [m]
    double pose;      //!< [deg]
} MyPosition;

typedef struct
{
    int x;  //!< [pixel]
    int y;  //!< [pixel]
} PixPosition;

typedef enum
{
    FRONT, //!< 前
    LEFT,  //!< 左
    REAR,  //!< 後
    RIGHT, //!< 右
} WheelPos;

typedef enum
{
    LASER_DEVICE,   // 0:Laser Scanner
    UBLOX5_DEVICE,  // 1:Ublox GPS
    A100_DEVICE,    // 2:A100
    COMPASS_DEVICE, // 3:Compass
    FOG_DEVICE,     // 4:FOG
    RX64_DEVICE,    // 5:RX64 Device
    IMCS01_DEVICE,  // 6:IMCS01
    JOYSTICK_DEVICE,// 7:Remote controller Joystick
    LASER_DEVICE2   // 8:Laser Scanner
} DeviceName;

double getTime();



#endif
