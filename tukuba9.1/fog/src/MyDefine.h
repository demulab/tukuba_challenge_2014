/*** A Tukuba Challenge Robot Control Program 2010 for demura.net ***/

//! 全体の定義用ファイル
/*! 全体に関係する定義は全てこのファイルに書くこと

 \file   MyDefine.h
 \author Kosei Demura
 \date   2010-09-07
*/


#ifndef _MY_DEFINE_H_
#define _MY_DEFINE_H_

// LOCALICATION_METHO
// 0.Particle Fileter with a100, 1.Particle Fileter with ublox5
// 2.Dead Reckoning with FOG, 3. Dead Reckoning with COMPASS, 4. Dead Reckoing with only Encoders,
// 5. A100, 6.UBLOX5
#define LOCALIZATION_METHOD 0

enum mode{
    PARTICLE_LOCALIZATION,
    RECKONING_FOG,
    RECKONING_COMPASS,
    RECKONING_ENCODERS,
};

//#define ODE　
//#define DEBUG
#define MY_VERSION  "2010-11-11" // バージョンの日付を入れる
#define WAYPOINTS_NUM 999         // ウェイポイント数
#define KIT_INIT_POSE 0          // KITでの初期姿勢[°]
#define TUKUBA_INIT_POSE  200    // TUKUBAでの初期姿勢[°]
#define START_WAYPOINT 0


/***パーティクルフィルタ関連***/
#define PARTICLE_NUM 1000    //パーティクルの個数
#define PARTICLE_RANGE 7    //パーティクルを撒く範囲[m]

/***ウェイポイント位置推定関連***/
#define WAY_PARTICLE_NUM 1000 //パーティクルの個数
#define WAY_PARTICLE_RANGE 7 //パーティクルを撒く範囲[m]

// 電子コンパスのオフセット
#define COMPASS_OFFSET_ANGLE  0 // この値を足すと正しい値になる

/*************************************************************************/
/*** 地図関連                                                          ***/
/*   地図を変更した場合は以下の設定を変更しなければならない     　　　   　　*/
/* 1. 地図ファイルの設定　                                                */
/* 2. 地図オフセットの設定（オプション）                                   */
/* 3. 地図の緯度経度とピクセル座標の対応設定                               */
/*************************************************************************/

// 1. 地図ファイルの設定：地図を変更した場合は以下の地図ファイルを変更
#define KIT_MAP    "maps/kitMap-Laser.jpg"    //!< KIT用地図
//#define KIT_MAP    "maps/the_third_floor.bmp"
#define TUKUBA_MAP "maps/low1525-101114.gif"    //!< つくば中央公園用地図
//#define TUKUBA_MAP "low1153-101114.gif"    //!< つくば中央公園

/*** 地図のオフセット設定　***/
#define KIT_OFFSET_X       0    // KIT地図のオフセット　x座標[pix]
#define KIT_OFFSET_Y       0    // 　                  y座標[pix]
#define TUKUBA_OFFSET_X    -1400   //　-750 つくば中央公園地図のオフセット
#define TUKUBA_OFFSET_Y    -700   //  -250


// 2. 地図ファイルのオフセット設定：この値を変更すると地図の初期位置がずれる
// 必要がなければ設定する必要はない
//

// 3. 地図の緯度経度とピクセル座標の対応設定
// 地図上の2点における緯度、経度とピクセル(x, y)を設定する。
// 精度を出すために2点は地図の左上と右下の離れた点を選ぶこと。
// 地図を変更したら必ず、この値を変更しなければならない
// kitMap090823.jpg  (136.62664711475372, 36.53195885528937 )  -> (128,  93) pix
// kitMap090823.jpg  (136.62862122058868, 36.53078425045223 )  -> (867, 641)
// 経度：KIT_MAP_LON[0]とピクセルx座標：KIT_MAP_POINT_X[0]が対応
// 経度：KIT_MAP_LON[1]とピクセルx座標：KIT_MAP_POINT_X[1]が対応
// 緯度：KIT_MAP_LAT[0]とピクセルy座標：KIT_MAP_POINT_Y[0]が対応
// 緯度：KIT_MAP_LAT[1]とピクセルy座標：KIT_MAP_POINT_Y[1]が対応
// なお、ピクセル座標はウインドウの左上隅が原点、x座標の正方向は右、y座標の正方向は下
// 以下のデータはmaps/kitMap090823.jpg
const double KIT_MAP_LON[2] = {136.62664711475372, 136.62862122058868};  // 経度
const double KIT_MAP_LAT[2] = { 36.53195885528937,    36.53078425045223} ; // 緯度
const int KIT_MAP_POINT_X[2] = { 128,  867};
const int KIT_MAP_POINT_Y[2] = {   93,  641};

const double TUKUBA_MAP_LON[2] = {140.10900735855103,140.1126927137375};  // longitude
const double TUKUBA_MAP_LAT[2] = { 36.086199308940024,36.0827094303493} ; // latitude
const int TUKUBA_MAP_POINT_X[2] = { 552,2931};
const int TUKUBA_MAP_POINT_Y[2] = { 280,3058};

//const double TUKUBA_MAP_LON[2] = {140.10901272296906, 140.11268198490143};  // longitude
//const double TUKUBA_MAP_LAT[2] = { 36.086212314409,    36.082718101047064} ; // latitude
//const int TUKUBA_MAP_POINT_X[2] = { 550,    2926};
//const int TUKUBA_MAP_POINT_Y[2] = { 292,  3085};
//const int TUKUBA_MAP_POINT_X[2] = { 128,    93};
//const int TUKUBA_MAP_POINT_Y[2] = { 867,  641};

/*** 地図設定終わり　***************************************************************/



/*****************************************************************************/
/******* さわるな危険： システムの変更や問題がない限りこれ以降は変更しないこと ********/
/****************************************************************************/

// スレッド周期時間の調整用待ち時間
#define IMCS01_WAIT_TIME       3*1000  // [us]
#define GPS_WAIT_TIME         33*1000  //100,000 [us]  = 100 [ms]
#define COMPASS_WAIT_TIME     33*1000  // [us]
#define LASER_WAIT_TIME       33*1000  // [us]
#define SPEAK_WAIT_TIME       99*1000
#define FOG_WAIT_TIME         33*1000


//速度制御のカウント周期
#define COUNTER_TIME         0.0   //[s]

// ウェイポイントのファイル名
#define TUKUBA_WAYPOINTS_FILE "waypoints/tukuba_way_points.txt"
//#define KIT_WAYPOINTS_FILE    "waypoints/kit_way_points.txt"
#define KIT_WAYPOINTS_FILE    "waypoints/the_third_floor.txt"

// 地図表示部分のウインドウサイズ
// Qt デザイナで地図表示部分mapAreaを変更した場合のみ以下をそれと同じ値に変更すること
#define WINDOW_WIDTH   1000  //3288
#define WINDOW_HEIGHT   800

// 金沢は平面直角座標系の第7系に属する　(http://www.gsi.go.jp/LAW/heimencho.html)
// 平面座標系のx軸は緯度方向、y軸は経度方向なので注意すること
// 平面直角座標系を止め、緯度方向を, 経度方向をxとする
// tukuba4までとLATとLONが逆になる。
// 1度が何mに相当するか？
// 36°00'00",  136°00'00" -> x（緯度方向）:  629.495 ｍ, y（経度方向）: -105182.717 ｍ　世界座標系　
// 37°00'00",  137°00'00" -> x: 110970.192 ｍ, y: -14833.801 ｍ
// 1度が何mに相当するか？
#define KIT_LAT_TO_METER    (110970.192 - 629.495)     //110k340.697m, 1 degress is 1839 * 60 m
#define KIT_LON_TO_METER    (105182.717 - 14833.801) //  90k348.916m,                1505.8*60
#define KIT_METER_TO_LAT  1/(110970.192-629.495)
#define KIT_METER_TO_LON  1/(105182.717-14833.801)


// つくば市は平面直角座標系の第9系に属する 緯度方向がx, 経度方向がy
// 平面直角座標系を止め、緯度方向を, 経度方向をxとする
// tukuba4までとLATとLONが逆になる。
// 35°30'00",  139°30'00" -> x: -55420.558 ｍ, y:-30240.162 ｍ
// 36°30'00",  140°30'00" -> x:   55682.949 ｍ, y: 59721.825 ｍ
// 1度が何mに相当するか？
#define TUKUBA_LAT_TO_METER    (55682.949 + 55420.558)     // 111k103.5071m, degress is 1851.7  * 60 m
#define TUKUBA_LON_TO_METER    (59721.825 + 30240.162)    //   89k961.987m,          1499.4 * 60
#define TUKUBA_METER_TO_LAT   1/ (55682.949 + 55420.558)     // 111k103.5071m, degress is 1851.7  * 60 m
#define TUKUBA_METER_TO_LON   1/ (59721.825 + 30240.162)    //   89k961.987m,          1499.4 * 60

#define PIX_TO_METER 0.1 // [m]
#define METER_TO_PIX 10 // [pix]

// この行はファイルの最後
#endif 
