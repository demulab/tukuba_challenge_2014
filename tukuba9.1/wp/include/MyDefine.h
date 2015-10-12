/*** WayPoint Maker 2011 http://demura.net ***/
//! 全体の定義用ファイル
/*! 全体に関係する定義は全てこのファイルに書くこと

 \file   MyDefine.h
 \author Kosei Demura
 \date   2011-11-03
*/

#ifndef _MY_DEFINE_H_
#define _MY_DEFINE_H_

#define MY_VERSION  "2013-02-27" // バージョンの日付を入れる
#define WAYPOINTS_NUM 999        // ウェイポイント数
#define KIT_INIT_POSE 0          // KITでの初期姿勢[°]
#define TUKUBA_INIT_POSE  227    // TUKUBAでの初期姿勢[°]
#define START_WAYPOINT 0

/*************************************************************************/
/*** 地図関連                                                          ***/
/*   地図を変更した場合は以下の設定を変更しなければならない     　　 　　*/
/* 1. 地図ファイルの設定　                                               */
/* 2. 地図オフセットの設定（オプション）                                 */
/* 3. 地図の緯度経度とピクセル座標の対応設定                             */
/*************************************************************************/

// 1. 地図ファイルの設定：地図を変更した場合は以下の地図ファイルを変更
#define MAP_DIRECTORY "~/ros-pkg/tukuba9.1/wp/maps" //!<　地図ファイルの場所を設定
#define KIT_MAP    "maps/fmt1.pgm"    //!< KIT用地図//屋外実験用
//#define KIT_MAP    "maps/kit_map.pgm"    //!< KIT用地図
//#define KIT_MAP    "maps/the_third_floor.bmp"
#define TUKUBA_MAP "maps/tukuba_map.pgm"    //!< つくば中央公園用地図
//#define TUKUBA_MAP "maps/map1.pgm"    //!< つくば中央公園用地図


// 2. 地図ファイルのオフセット設定：この値を変更すると地図の初期位置がずれる
// 必要がなければ設定する必要はない
#define KIT_OFFSET_X       0    // KIT地図のオフセット　x座標[pix]
#define KIT_OFFSET_Y       0    // 　                  y座標[pix]
#define TUKUBA_OFFSET_X   -500   //　-5000 つくば中央公園地図のオフセット
#define TUKUBA_OFFSET_Y   -3800   //  -3800

// 3. 地図の緯度経度とピクセル座標の対応設定
// 地図上の1点における緯度、経度とピクセル(x, y)を設定する。
// 精度を出すために2点は地図の左上と右下の離れた点を選ぶこと。
// 2点で設定する理由は地図が必ずしも北が上でないことによる。
// 1mに対応する緯度経度の差は緯度により異なる。
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
const double KIT_MAP_LAT[2] = { 36.53195885528937,  36.53078425045223} ; // 緯度
const int KIT_MAP_POINT_X[2] = { 0, 1783};
const int KIT_MAP_POINT_Y[2] = { 0, 1296};

const double TUKUBA_MAP_LON[2] = {140.10900735855103,140.1126927137375};  // longitude
const double TUKUBA_MAP_LAT[2] = { 36.086199308940024,36.0827094303493} ; // latitude
const int TUKUBA_MAP_POINT_X[2] = { 0, 3315};
const int TUKUBA_MAP_POINT_Y[2] = { 0, 3877};

/*** 地図設定終わり　***************************************************************/
// ウェイポイントのファイル名
#define TUKUBA_WAYPOINTS_FILE    "tukuba_waypoints.txt"      // 緯度経度
#define TUKUBA_WAYPOINTS_XY_FILE "tukuba_waypoints_xy.txt"   // xy
//#define KIT_WAYPOINTS_FILE    "waypoints/kit_way_points.txt"
#define KIT_WAYPOINTS_FILE       "kit_waypoints.txt"
#define KIT_WAYPOINTS_XY_FILE    "kit_waypoints_xy.txt"

#define PIX_TO_METER 0.1 // 0.1 [m]
#define METER_TO_PIX (1.0/PIX_TO_METER) // 10 [pix]

// ここから下は変更してはならない
// 金沢は平面直角座標系の第7系に属する　(http://www.gsi.go.jp/LAW/heimencho.html)
// 平面座標系のx軸は緯度方向、y軸は経度方向なので注意すること
// 平面直角座標系を止め、緯度方向を, 経度方向をxとする
// 1度が何mに相当するか？
// 36°00'00",  136°00'00" -> x（緯度方向）:  629.495 ｍ, y（経度方向）: -105182.717 ｍ　世界座標系　
// 37°00'00",  137°00'00" -> x: 110970.192 ｍ, y: -14833.801 ｍ
// 1度が何mに相当するか？
#define KIT_LAT_TO_METER    (110970.192 - 629.495)     //110k340.697m, 1 degress is 1839 * 60 m
#define KIT_LON_TO_METER    (105182.717 - 14833.801) //  90k348.916m,                1505.8*60
#define KIT_METER_TO_LAT  (1.0/KIT_LAT_TO_METER)
#define KIT_METER_TO_LON  (1.0/KIT_LON_TO_METER)

// つくば市は平面直角座標系の第9系に属する. 緯度方向がx, 経度方向がy
// 平面直角座標系を止め、緯度方向をy, 経度方向をxとする
// 35°30'00",  139°30'00" -> x: -55420.558 ｍ, y:-30240.162 ｍ
// 36°30'00",  140°30'00" -> x:   55682.949 ｍ, y: 59721.825 ｍ
// 1度が何mに相当するか？
#define TUKUBA_LAT_TO_METER    (55682.949 + 55420.558)     // 111k103.5071m, degress is 1851.7  * 60 m
#define TUKUBA_LON_TO_METER    (59721.825 + 30240.162)    //   89k961.987m,          1499.4 * 60
#define TUKUBA_METER_TO_LAT   (1.0/TUKUBA_LAT_TO_METER)   // 111k103.5071m, degress is 1851.7  * 60 m
#define TUKUBA_METER_TO_LON   (1.0/TUKUBA_LON_TO_METER)   //   89k961.987m,          1499.4 * 60

// 地図表示部分のウインドウサイズ
// Qt デザイナで地図表示部分mapAreaを変更した場合のみ以下をそれと同じ値に変更すること
#define WINDOW_WIDTH   1150  //3288
#define WINDOW_HEIGHT   800

// この行はファイルの最後
#endif 
