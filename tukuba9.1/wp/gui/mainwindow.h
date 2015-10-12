/*** WayPoint Maker 2011 http://demura.net ***/

//! GUIのメイン関数
/*!
 \file   mainwindow.h
 \author Kosei Demura
 \date   2011-11-03
*/

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui/QMainWindow>
#include "gui.h"

//! QT用のネームスペース
namespace Ui
{
    class MainWindow;
}

//! メインウインドウクラス
class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();
    Ui::MainWindow *ui;
    GuiClass *map;

public slots:
    void aboutProgram();   //!< プログラムの概要表示
    void setKIT();         //!< KITの環境設定
    void setTukuba();      //!< つくばの環境設定
    void saveWaypoints();  //!< ウェイポイントの保存
    void hideInfo();       //!< 情報を隠す
    void hideWaypoints();  //!< ウェイポイントを隠す
    void speakIntro();     //!< 自己紹介の発話
    void showWaypoint200(); //!< ウェイポイントを200個まで設定
    void showOpenFileDialog();
    // void loadFromFile();    //!< ファイルを開く
protected:
    virtual void paintEvent(QPaintEvent* event);

private:
    QAction*    setKitAction;
    QAction*    setTukubaAction;
    QAction*    quitAction;
    QAction*    saveAction;
    QAction*    aboutAction;
    QAction*    findMapAction;
    QAction*    hideInfoAction;
    QAction*    hideWaypointsAction;
    QAction*    setWaypointsAction;
    QAction*    showWaypointsAction;
    QAction*    speakAction;
    QAction*    createMapAction;
    QMenu*      fileMenu;
    QMenu*      logMenu;
    QMenu*      aboutMenu;
    QToolBar*   fileToolBar;
    void setWayPoint(int i, bool checked);
    void setWayPoint2(int i);
    void setWayPoint4(int i, int pose);
    bool waypoints_locked; // ウェイポイントを設定可能にする変数

private slots:
    void on_wpRadioOnBtn_clicked();  //!< ウェイポイント設定ラジオボタン
    void on_scaleSlider_valueChanged(int value);
};

//! メイン関数の引数をスレッドに渡すための構造体
typedef struct
{
    int argc;
    char **argv;
} MyArgument;

//! GUIスレッド関数
void *guiThread(void *);


#endif // MAINWINDOW_H
