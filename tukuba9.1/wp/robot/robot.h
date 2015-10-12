/*** WayPoint Maker 2011 http://demura.net ***/

//! ロボットクラスを定義しているヘッダファイル
/*! ロボットクラスを定義しているヘッダファイル

\file  robot.h
\author Kosei Demura
\date 　2010-09-13
*/

/*! \mainpage  A Tukuba Challenge Robot Control Program 2010

\section はじめに

つくばチャレンジ2010の完走を目指すプログラム。各センサ、ナビゲーション、自己位置推定に
対応するスレッドを生成し、全スレッドに共通の情報はrobotクラスに読み書きする。いわゆる、古典的な黒板モデルである。

\section Copyright

このドキュメントの著作権はKosei Demuraとdemura.netチームが保有している。
*/

#ifndef _ROBOT_H_
#define _ROBOT_H_

#include "include/MyDefine.h"
#include "include/common.h"
#include <string>

//#include "imcs01/imcs01.h"
//#include "gps2/gps2.h"
//#include "laser/laser.h"
//#include "compass/compass.h"
//#include "gui/gui.h"
//#include "fog/fog.h"
//#include "icp/icp.h"
//#include "navigation/navigation.h"

//! ロボットクラス
/*!
  ロボット全ての情報を保持している最も重要なクラス
*/
class RobotClass
{
private:
    double x0, y0, pose0; //!< 初期位置[m]と初期姿勢[rad] デッドレコニング座標系
    double x, y, pose;    //!< 位置[m], 姿勢[rad]
    double p_x;           //!< パーティクルフィルタによる自己位置x座標 [m]
    double p_y;           //!< パーティクルフィルタによる自己位置y座標 [m]
    double p_pose;        //!< パーティクルフィルタによる姿勢 [rad]
    double longitude;     //!< 経度 [deg]
    double latitude;      //!< 緯度 [deg]

public:
    // Imcs01Class      *imcs01;       //!< icms01
    // GpsClass         *ublox5,*a100; //!< GPS ublox5, a100
    // LaserClass       *laser;        //!< レーザスキャナ
    // CompassClass     *compass;      //!< 電子コンパス
    // FogClass         *fog;          //!< FOG（光ファイバジャイロ）
    // IcpClass         *icp;
    // NavigationClass  *navigation;   //!< ナビゲーション

    //string devices[10];   //!< デバイスファイルを格納

    bool gps_on, gps2_on; //!< true: GPS on,     false: GPS off
    bool laser_on;        //!< true: laser on,   false: laser off
    bool imcs_on;         //!< true: imcs on,    false: imcs off
    bool compass_on;      //!< true: compass on, false: compass off
    // bool map_movable;     //!< true: 地図移動,   false: 地図固定
    bool control;      //!< true: autonomous,  false: remote control
    bool stop;         //!< true: stop,        false: active
    bool tukuba;       //!< true: tukuba,      false: KIT
    bool record;       //!< if true then record logs, or not
    bool play_log;     //!< true: play log,
    bool hide_info;    //!< true: hide info, false; show info
    bool hide_waypoints_info; //!< true: hide waypoints info, false; show info
    bool test;         //!< true: test running false: normal running
    bool waypoint_estimation; //!< true: way_point_estimation on, false: off
    bool obstty;

    double elapsed_time; //!< 経過時間
    double start_time;   //!< スタート時間
    double stop_time;    //!< ストップ時間


    int draw_x0, draw_y0; //!< 画面の左上点（ずれ、倍率、オフセット含む）
    double speed_turn;    //!< 旋回スピード [rad/s]
    double speed_forward; //!< 直進スピード [m/s]


    double target_course;     //!< 目標針路 [rad]
    double gravity_course;    //!< 引力の向き [rad]
    double repulsive_course;  //!< 斥力の向き
    char  words[100];         //!< 話す言葉

    MyPosition waypoint[WAYPOINTS_NUM];  //!< ウェイポイント配列
    int next_waypoint; //!< 次のウェイポイント
    PixPosition rightClickPos; //!< 右マウスボタンをクリックした画面上での位置
    PixPosition leftClickPos;  //!< 右マウスボタンをクリックした画面上での位置

    RobotClass();   //!< コンストラクタ
    ~RobotClass();  //!< デストラクタ

    double getX();         //!< 位置x座標の取得[m]
    double getY();         //!< 位置y座標の取得[m]
    double getPose();      //!< 姿勢の取得[rad]
    double getX0();        //!< 初期位置x座標の取得[m]
    double getY0();        //!< 初期位置y座標の取得[m]
    double getPose0();     //!< 初期姿勢の取得[rad]
    double getP_X();       //!< パーティクルフィルタによる位置x座標の取得[m]
    double getP_Y();       //!< パーティクルフィルタ位置y座標の取得[m]
    double getP_Pose();    //!< パーティクルフィルタ姿勢の取得[rad]
    double getLatitude();  //!< 緯度の取得[deg]
    double getLongitude(); //!< 経度の取得[deg]

    void setX(double val);         //!< 位置x座標の設定[m]
    void setY(double val);         //!< 位置y座標の設定[m]
    void setPose(double val);      //!< 姿勢の設定[rad]
    void setX0(double val);        //!< 初期位置x座標の設定[m]
    void setY0(double val);        //!< 初期位置y座標の設定[m]
    void setPose0(double val);     //!< 初期姿勢の設定[rad]
    void setP_X(double val);       //!< パーティクルフィルタによる位置x座標の設定[m]
    void setP_Y(double val);       //!< パーティクルフィルタ位置y座標の設定[m]
    void setP_Pose(double val);    //!< パーティクルフィルタ姿勢の設定[rad]
    void setLatitude(double val);  //!< 緯度の設定[deg]
    void setLongitude(double val); //!< 経度の設定[deg]#include "../include/common.h"
    void setWaypoint(int n, double way_x, double way_y); //!< ウェイポイントの緯度、経度設定
    void speak(char *);  //!< 発話する
    void nowords();      //!< 発話しない


    /* void speak(char *s)   {
        strcpy(words, s);
    }

    void nowords()
    {
        char s[100];
        strcpy(words,s);
    }

    char *getWords()
    {
        return (char *) words;
    } */
};

#endif
