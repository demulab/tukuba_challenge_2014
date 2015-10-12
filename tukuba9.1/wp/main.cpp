/*** Waypoint Maker 2011 http://demura.net ***/

//! メイン関数
/*! メイン関数。ここから全てのスレッドを起動する。

\file  main.cpp
\author Kosei Demura
\date 　2011-11-03
*/

#include <fstream>
#include <iostream>

#include "robot/robot.h"
#include <QtGui/QApplication>   // Qt用
#include "gui/mainwindow.h"     // Qt用

using namespace std;

#define THREAD_NO 11 //!<  スレッド数

//スレッドの有無をここで決定する
#define GUI

RobotClass  *robot     = new RobotClass;

//! メイン関数
int main(int argc, char *argv[])
{
    pthread_t thread[THREAD_NO];

    // GUIスレッドの生成. main関数の引数を渡している
    MyArgument gui_arg;
    gui_arg.argc = argc;
    gui_arg.argv = argv;

#ifdef GUI
    pthread_create(&thread[5], NULL, guiThread, &gui_arg);

    // スレッドの終了をmain関数（メインスレッド）が待つ
    // これがないとmain関数が終了した時点で、子スレッドも死んでしまう
    pthread_join(thread[5], NULL);//GUI
#endif

    return 0;
}
