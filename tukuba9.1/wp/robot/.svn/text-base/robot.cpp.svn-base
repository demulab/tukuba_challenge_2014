/*** WayPoint Maker 2011 http://demura.net ***/

//! robot関数。ロボットクラスを定義している。
/*! robot関数。最も重要なロボットクラスを定義している。

\file  main.cpp
\author Kosei Demura
\date 　2010-09-13
*/

#include "robot.h"
#include <fstream>
#include <string.h>

//! ロボットクラスのコンストラクタ
RobotClass::RobotClass() // constructor
{
    //gps_on   = false;
    //laser_on = false;
    //imcs_on = false;
    stop     = true;    //!< true: ロボット停止,  false: ロボット可動
    control  = true;    //!< true: ロボット自動制御, false: リモコン
    tukuba   = true;   //!< true:つくば,  false: KIT
    record   = false;   //!< true:ログ記録, false: 不記録
    test     = false;   //!< true:テスト走行, false: 本走行
    play_log = false;   //!< true:ログ再生,  false: 不再生


    // map_movable = true;          //!< true: 地図移動機能ON,  false:OFF
    hide_info = false;            //!< true: 情報表示, false: 非表示
    hide_waypoints_info = false; //!< true:情報表示, false: 非表示
    waypoint_estimation = true;  //!< true:ウェイポイント修正アルゴリズム使用, 非使用
    obstty = true;               //!< true:障害物補間on

    start_time   = 0;
    stop_time    = 0;
    elapsed_time = 0;

    target_course=0;

    rightClickPos.x   = WINDOW_WIDTH   / 2.0;  //!< ウインドウサイズの中心
    rightClickPos.y   = WINDOW_HEIGHT  / 2.0;
    leftClickPos.x    = 0;
    leftClickPos.y    = 0;

    //自己位置計算用変数の初期化
    p_x    = 0.0;
    p_y    = 0.0;
    p_pose = 0.0;


    for (int i = 0; i < WAYPOINTS_NUM; i++)
    {
        waypoint[i].latitude   = 0.0;
        waypoint[i].longitude  = 0.0;
        waypoint[i].offset    = 0.0;
    }

    if (tukuba) {
        draw_x0 = TUKUBA_OFFSET_X;
        draw_y0 = TUKUBA_OFFSET_Y;
    }
    else {
        draw_x0 = KIT_OFFSET_X;
        draw_y0 = KIT_OFFSET_Y;
    }

    for (int i = 0; i < 100; i++) {
        words[i] = 0;
    }





}

//! デストラクタ
RobotClass::~RobotClass()
{
}

//! 位置x座用の取得 [m]
double RobotClass::getX()
{
    return x;
}

//! 位置y座用の取得 [m]
double RobotClass::getY()
{
    return y;
}

//! 姿勢の取得 [rad]
double RobotClass::getPose()
{
    return pose;
}

//! 初期位置x座用の取得 [m]
double RobotClass::getX0()
{
    return x0;
}

//! 初期位置y座用の取得 [m]
double RobotClass::getY0()
{
    return y0;
}

//! 初期姿勢の取得 [rad]
double RobotClass::getPose0()
{
    return pose0;
}

//! パーティクルフィルタの位置x座用の取得 [m]
double RobotClass::getP_X()
{
    return p_x;
}

//! パーティクルフィルタの位置y座用の取得 [m]
double RobotClass::getP_Y()
{
    return p_y;
}

//! パーティクルフィルタの姿勢の取得 [rad]
double RobotClass::getP_Pose()
{
    return p_pose;
}

//! 緯度の取得 [deg]
double RobotClass::getLatitude()
{
    return latitude;
}

//! 経度の取得 [deg]
double RobotClass::getLongitude()
{
    return longitude;
}

//! 初期位置x座用の設定 [m]
void RobotClass::setX0(double val)
{
    x0 = val;
}

//! 初期位置y座用の設定 [m]
void RobotClass::setY0(double val)
{
    y0 = val;
}

//! 初期姿勢の設定 [rad]
void RobotClass::setPose0(double val)
{
    pose0 = val;
}

//! 位置x座用の設定 [m]
void RobotClass::setX(double val)
{
    x = val;
}

//! 位置y座用の設定 [m]
void RobotClass::setY(double val)
{
    y = val;
}

//! 姿勢の設定 [rad]
void RobotClass::setPose(double val)
{
    pose = val;
}

//! パーティクルフィルタの位置x座用の設定 [m]
void RobotClass::setP_X(double val)
{
    p_x = val;
}

//! パーティクルフィルタの位置y座用の設定 [m]
void RobotClass::setP_Y(double val)
{
    p_y = val;
}

//! パーティクルフィルタの姿勢の設定 [rad]
void RobotClass::setP_Pose(double val)
{
    p_pose = val;
}

//! ウェイポイントの設定
void RobotClass::setWaypoint(int n,double way_x, double way_y)    {

    if(tukuba == false){
        waypoint[n].longitude  =  way_x * KIT_METER_TO_LON + waypoint[START_WAYPOINT].longitude;
        waypoint[n].latitude   =  way_y * KIT_METER_TO_LAT + waypoint[START_WAYPOINT].latitude;
    }
    else{
        waypoint[n].longitude  =  way_x * TUKUBA_METER_TO_LON + waypoint[START_WAYPOINT].longitude;
        waypoint[n].latitude   =  way_y * TUKUBA_METER_TO_LAT + waypoint[START_WAYPOINT].latitude;
    }
}

//! 緯度の設定 [deg]
void RobotClass::setLatitude(double val)
{
    latitude = val;
}

//! 経度の設定 [deg]
void RobotClass::setLongitude(double val)
{
    longitude = val;
}


//! 発話する
void RobotClass::speak(char *s)   {
     strcpy(words, s);
}

//! 発話しない
void RobotClass::nowords()
{
     char s[100];
     for (int i=0; i < sizeof(s); i++) s[i] = '\0';
}
