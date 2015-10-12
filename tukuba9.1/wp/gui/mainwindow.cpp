//! GUIプログラムのメイン
/*! コントロールパネルの中心部分

    \file   mainwidow.cpp
    \author Kosei Demura
    \date   2010-09-07
*/

// WayPoint Maker 2011,   Kosei Demura
// mainwindow.cpp
// コントロールパネルの中心部分

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "showwaypoint.h"
#include "../include/MyDefine.h"
#include "../include/common.h"
#include "../robot/robot.h"
#include "gui.h"
using namespace std;

extern RobotClass *robot;
MainWindow *gwindow;
GuiClass *map;

// GUI スレッド
void *guiThread(void *args)
{
    int tmp_argc;
    char **tmp_argv;


    // main関数の引数をスレッドに渡すためにキャスト
    tmp_argc = ((MyArgument *) args)->argc;
    tmp_argv = ((MyArgument *) args)->argv;

    // 文字化防止
    QApplication a(tmp_argc, tmp_argv);
    QTextCodec *codec = QTextCodec::codecForName("UTF-8");
    QTextCodec::setCodecForTr(codec);
    QTextCodec::setCodecForCStrings(codec);
    QTextCodec::setCodecForLocale(codec);

      // ウィジットのスタイルを以下の中から選択可能
    // WindowsVista, cde, motif, plastique, windows, macintosh, cleanlooks
    // a.setStyle("windows");
    a.setStyle("macintosh");
    
    // MainWindow gwindow;
    gwindow = new MainWindow;
    gwindow->show();             // 　メインウインドウの表示
    a.exec();                    // 　イベントループ
}

//　MainWindowクラス：メインウインドウに関するクラス
// コンストラクタ
MainWindow::MainWindow(QWidget *parent)
        : QMainWindow(parent), ui(new Ui::MainWindow)
{
    // Gui Class

    ui->setupUi(this);
    // ui->auto_btn->setChecked(true);
    // ui->movable_btn->setChecked(true); // 移動ボタンにチェック

    waypoints_locked = true; // ウェイポインタが変更されないようにロック

    map = new GuiClass(ui->scrollArea);

    // Info Class
    //ui->infoBox->setGeometry(QRect(0, 0, 250, 600));

    // Speed Meter
    //ui->speedMeter->setStyle(new QMotifStyle);
    //ui->speedMeter->setStyleSheet("* { color: black; background-color:rgb(255, 0, 0); padding: 7px}}");
    //ui->speedMeter->setStyleSheet("* { color: black; background-color:rgb(0, 0, 0); padding: 7px}}");

    // heading Meter
    //ui->headingMeter->setStyle(new QMotifStyle);
    //ui->headingMeter->setStyleSheet("* { background-color:rgb(0, 0, 255); padding: 7px}}");
    //ui->headingMeter->setStyleSheet("* { background-color:rgb(0, 0, 0); padding: 7px}}");

    // spin box for waypoints
    /* ui->spinBoxWaypoints->setRange(0, 50);
    ui->spinBoxWaypoints->setValue(0);
    ui->spinBoxWaypoints->setSingleStep(1);
    ui->set_btn->setChecked(false);
    ui->lock_btn->setChecked(true); */

    // Set the window title
    QString s1 = "Way Point Maker ";
    QString s2 = MY_VERSION;
    QString s3 = s1 + s2 + " http://demura.net";
    setWindowTitle(s3);

    // Load KIT action
    setKitAction = new QAction(tr("&KIT"), this);
    setKitAction->setIcon(QIcon("images/kit.jpg"));
    setKitAction->setShortcut(tr("Ctrl+K"));
    setKitAction->setStatusTip(tr("Load the KIT environment"));
    connect(setKitAction, SIGNAL(triggered()), this, SLOT(setKIT()));

    // Load Tukuba action
    setTukubaAction = new QAction(tr("&つくば"), this);
    setTukubaAction->setIcon(QIcon("images/tukuba.jpg"));
    setTukubaAction->setShortcut(tr("Ctrl+T"));
    setTukubaAction->setStatusTip(tr("Load the Tukuba environment"));
    connect(setTukubaAction, SIGNAL(triggered()), this, SLOT(setTukuba()));

    // save action
    saveAction = new QAction(tr("&経由点\n保存"), this);
    saveAction->setIcon(QIcon("images/save.png"));
    saveAction->setShortcut(tr("Ctrl+S"));
    saveAction->setStatusTip(tr("Save the way points"));
    connect(saveAction, SIGNAL(triggered()), this, SLOT(saveWaypoints()));

    // quit action
    quitAction = new QAction(tr("&Quit"), this);
    quitAction->setShortcut(tr("Ctrl+Q"));
    quitAction->setIcon(QIcon("images/quit.png"));
    quitAction->setStatusTip(tr("Quit the application"));
    connect(quitAction, SIGNAL(triggered()), this, SLOT(close()));

    // about action
    aboutAction = new QAction(tr("&About"), this);
    aboutAction->setStatusTip(tr("About Tukuba Controller"));
    connect(aboutAction, SIGNAL(triggered()), this, SLOT(aboutProgram()));

    // show/hide info
    hideInfoAction = new QAction(tr("&使い方\n表示/隠す"), this);
    //hideInfoAction->setIcon(QIcon("images/play.jpg"));
    hideInfoAction->setStatusTip(tr("Hide/Show Info"));
    connect(hideInfoAction, SIGNAL(triggered()), this, SLOT(hideInfo()));

    // show/hide info
    hideWaypointsAction = new QAction(tr("&経由点\n表示/隠す"), this);
    //hideInfoAction->setIcon(QIcon("images/play.jpg"));
    hideWaypointsAction->setStatusTip(tr("Hide/Show Waypoints"));
    connect(hideWaypointsAction, SIGNAL(triggered()), this, SLOT(hideWaypoints()));

    // Speak Intro
    speakAction = new QAction(tr("&発話"), this);
    speakAction->setIcon(QIcon("images/speak.png"));
    speakAction->setStatusTip(tr("Speak"));
    connect(speakAction, SIGNAL(triggered()), this, SLOT(speakIntro()));

    // Show Waypoint action
    showWaypointsAction = new QAction(tr("&経由点\n表示"), this);
    // createMapAction->setIcon(QIcon("images/createmap.jpg"));
    showWaypointsAction->setStatusTip(tr("Show\nWaypoints"));
    connect(showWaypointsAction, SIGNAL(triggered()), this, SLOT(showWaypoint200()));

    // find log file Tukuba action
    findMapAction = new QAction(tr("&地図を開く"), this);
    findMapAction->setShortcut(tr("Ctrl+M"));
    findMapAction->setStatusTip(tr("地図を開く"));
    connect(findMapAction, SIGNAL(triggered()), this, SLOT(showOpenFileDialog()));

    // メニューバー
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(findMapAction);
    fileMenu->addAction(setKitAction);
    fileMenu->addAction(setTukubaAction);
    fileMenu->addAction(saveAction);
    fileMenu->addAction(quitAction);

    aboutMenu = menuBar()->addMenu(tr("&Help"));
    aboutMenu->addAction(aboutAction);

    // ツールバー
    ui->toolBar = addToolBar(tr("&File"));
    ui->toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);  
    ui->toolBar->addAction(setKitAction);
    ui->toolBar->addAction(setTukubaAction);
    ui->toolBar->addAction(saveAction);
    ui->toolBar->addAction(hideInfoAction);
    ui->toolBar->addAction(showWaypointsAction);
    ui->toolBar->addAction(speakAction);

}

// デストラクタ
MainWindow::~MainWindow()
{
    delete ui;
}

//! ウェイポイントの設定
// 各ウェイポイントのラジオボタンをクリックするとウェイポイントが設定可能
void MainWindow::setWayPoint(int i, bool checked)
{
   // ラジオボタンがチェックされ、倍率が１倍のとき
   // if (checked && map->getScale() == 1.0)
     if (checked && map->getScale() != 0.0)

    {
        int offset_x = 0, offset_y = 0;
        if (robot->tukuba)
        {
            offset_x = TUKUBA_OFFSET_X;
            offset_y = TUKUBA_OFFSET_Y;
        }
        else {
            offset_x = KIT_OFFSET_X;
            offset_y = KIT_OFFSET_Y;            
        }
        // robot->leftClickPosはマウス左ボタンのクリックにより地図を移動できるので、その分を補正している
        //robot->waypoint[i].longitude = map->pixToLon((robot->rightClickPos.x
        //                               - (int) (0.5 * WINDOW_WIDTH) + robot->leftClickPos.x - offset_x)/map->getScale());
        //robot->waypoint[i].latitude   = map->pixToLat((robot->rightClickPos.y
        //                                - (int) (0.5 * WINDOW_HEIGHT) + robot->leftClickPos.y - offset_y)/map->getScale());
        robot->waypoint[i].longitude = map->pixToLon((robot->rightClickPos.x
                                        - robot->draw_x0 - offset_x)/map->getScale());
        robot->waypoint[i].latitude   = map->pixToLat((robot->rightClickPos.y
                                        - robot->draw_y0 - offset_y)/map->getScale());
    }
}

// スピンボックスを利用したウェイポイントの設定(未実装）
// 表示が重く操作感が悪かったので使用を止めた
void MainWindow::setWayPoint2(int i)
{
   // ラジオボタンがチェックされ、倍率が１倍のとき
     if (waypoints_locked)

    {
        int offset_x = 0, offset_y = 0;
        if (robot->tukuba)
        {
            offset_x = TUKUBA_OFFSET_X;
            offset_y = TUKUBA_OFFSET_Y;
        }
        else {
            offset_x = KIT_OFFSET_X;
            offset_y = KIT_OFFSET_Y;
        }
        // robot->leftClickPosはマウス左ボタンのクリックにより地図を移動できるので、その分を補正している
        robot->waypoint[i].longitude = map->pixToLon((robot->rightClickPos.x
                                       - (int) (0.5 * WINDOW_WIDTH) + robot->leftClickPos.x - offset_x)/map->getScale());
        robot->waypoint[i].latitude   = map->pixToLat((robot->rightClickPos.y
                                        - (int) (0.5 * WINDOW_HEIGHT) + robot->leftClickPos.y - offset_y)/map->getScale());
    }
}


// Helpメニュー用
void MainWindow::aboutProgram()
{
    QMessageBox::about(this, tr("About..."),
                       tr("<p> Welcome to  A Tukuba Challenge Control Panel ! </p>"
                          "<p> This program is developed by Kosei Demura. </p>"));
}

// ファイルメニュー用
// つくば環境を設定
void MainWindow::setTukuba()
{
    robot->tukuba = true;
    map->setupEnv();
}

// KIT環境を設定
void MainWindow::setKIT()
{
    robot->tukuba = false;
    map->setupEnv();
}

// ウェイポイントの保存
void MainWindow::saveWaypoints()
{
    // 緯度経度保存
    QFile file;
    if (robot->tukuba) file.setFileName(TUKUBA_WAYPOINTS_FILE);
    else               file.setFileName(KIT_WAYPOINTS_FILE);

    if (!file.open(QIODevice::WriteOnly))
    {
        cerr << " cannot open file for waypoints writing: "
        << qPrintable(file.errorString()) << endl;
        return;
    }

    QTextStream out(&file);

    for (int i = 0; i < WAYPOINTS_NUM; i++)
    {
        //out <<  i << ","  << qSetRealNumberPrecision(12) << robot->waypoint[i].latitude
        //<< "," << robot->waypoint[i].longitude << "," << robot->waypoint[i].offset << endl;

        // latitude and longitude
        out <<  i << ","  << qSetRealNumberPrecision(12) << robot->waypoint[i].latitude
        << "," << robot->waypoint[i].longitude << "," << robot->waypoint[i].pose <<"," << endl;

        //out <<  i << ","  << qSetRealNumberPrecision(6) << robot->waypoint[i].x
        //<< "," << robot->waypoint[i].y << "," << robot->waypoint[i].pose << endl;

    }

    // xy保存
    QFile file2;
    if (robot->tukuba) file2.setFileName(TUKUBA_WAYPOINTS_XY_FILE);
    else               file2.setFileName(KIT_WAYPOINTS_XY_FILE);

    if (!file2.open(QIODevice::WriteOnly))
    {
        cerr << " cannot open file for waypoints writing: "
        << qPrintable(file2.errorString()) << endl;
        return;
    }

    QTextStream out2(&file2);

    for (int i = 0; i < WAYPOINTS_NUM; i++)
    {
        out2 <<  i << ","  << qSetRealNumberPrecision(6) << robot->waypoint[i].x
        << "," << robot->waypoint[i].y << "," << robot->waypoint[i].pose << "," << endl;

    }
}


// 2010-11-09 demu
// ウェイポイント表示用のウインドウを開く
void MainWindow::showWaypoint200()
{
    ShowWaypointClass *dialog2 = new ShowWaypointClass();

    dialog2->exec();
    delete dialog2;
}

//! 情報の隠蔽
void MainWindow::hideInfo()
{
    if (robot->hide_info == false) {
        robot->hide_info = true;
    }
    else {
        robot->hide_info = false;
    }
}

//! ウェイポイントの隠蔽
void MainWindow::hideWaypoints()
{
    if (robot->hide_waypoints_info == false) {
        robot->hide_waypoints_info = true;
    }
    else {
        robot->hide_waypoints_info = false;
    }
}

void MainWindow::speakIntro()
{
    system("aplay speak/start.wav");
    system("aplay speak/demuranet.wav");
    system("aplay speak/kanso.wav");
    system("aplay speak/ganbarimasu.wav");
    system("aplay speak/5.wav");
    system("aplay speak/4.wav");
    system("aplay speak/3.wav");
    system("aplay speak/2.wav");
    system("aplay speak/1.wav");
    system("aplay speak/startbtn.wav");
}


//! スライダーによる地図縮尺の変更
void MainWindow::on_scaleSlider_valueChanged(int value)
{
    map->setScale((double) value);
}

/* void MainWindow::showOpenFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                 tr("地図を開く"),"/home/demulab/ros-pkg/tukuba8/maps",
                                 tr("Image Files (*.gif *.jpg *.pgm)"));
    if (fileName.isEmpty())
        return;
    else {
        map->openFile(fileName);
    }
} */


void MainWindow::showOpenFileDialog()
{
    QString fileName = QFileDialog::getOpenFileName(this,
                                 tr("地図を開く"),"./maps",
                                 tr("Image Files (*.gif *.jpg *.pgm *.png)"));
    if (fileName.isEmpty()) {
        cout << "I cannot find " << MAP_DIRECTORY << endl;
        return;
    }
    else {
        cout << "I find " << MAP_DIRECTORY << endl;
        map->openFile(fileName);
    }
}

// 速度計と針路計の表示
void MainWindow::paintEvent(QPaintEvent *)
{
    QPainter painter(this);
    QPen pen_red(Qt::red);
    QPen pen_blue(Qt::blue);
    QPen pen_black(Qt::black);

    pen_red.setWidth(5);
    pen_blue.setWidth(5);
    painter.setPen(pen_black);
    painter.setFont(QFont("Arial", 16));
    pen_black.setWidth(10);
    pen_black.setWidth(5);

    update();
}

//! ウェイポイントの設定
// 各ウェイポイントのラジオボタンをクリックするとウェイポイントが設定可能
void MainWindow::setWayPoint4(int i, int pose)
{
   // 倍率が１倍のとき
   // if (map->getScale() == 1.0)
    if (map->getScale() != 0.0)
    {
        int offset_x = 0, offset_y = 0;
        if (robot->tukuba)
        {
            offset_x = TUKUBA_OFFSET_X;
            offset_y = TUKUBA_OFFSET_Y;
        }
        else {
            offset_x = KIT_OFFSET_X;
            offset_y = KIT_OFFSET_Y;
        }

		if(i == 0)
		{
		/*
			std::cout<< "robot->rightClickPos.x = " << robot->rightClickPos.x <<std::endl;
			std::cout<< "robot->rightClickPos.y = " << robot->rightClickPos.y <<std::endl;
			std::cout<< "robot->draw_x0 = " << robot->draw_x0 <<std::endl;
			std::cout<< "robot->draw_y0 = " << robot->draw_y0 <<std::endl;
			std::cout<<"offset_x = " << offset_x << std::endl;
			std::cout<<"offset_y = " << offset_y << std::endl;
		*/
			double pixcel_x = robot->rightClickPos.x - robot->draw_x0;
			double  pixcel_y = robot->rightClickPos.y - robot->draw_y0;
			std::cout<< "pixcel x = " << pixcel_x <<std::endl;
			std::cout<< "pixcel y = " << pixcel_y <<std::endl;	
			std::cout<< "以下の2つは、ROSのmap.yamlファイルのorigineに合わせた原点" <<std::endl;	
			//std::cout<< "map width = " << map->getWidth() <<std::endl;	
			//std::cout<< "map height = " << map->getHeight() <<std::endl;
			std::cout<< "x[m] = " << -pixcel_x * map->getScale() * PIX_TO_METER <<std::endl;
			std::cout<< "y[m] = " << -( (double)(map->getHeight()) - pixcel_y) * map->getScale() * PIX_TO_METER <<std::endl;	
			
			FILE *file;
			file = fopen("wp0_pixcel.txt", "a");
			fprintf(file, "%lf,%lf \n", pixcel_x, pixcel_y );
			fclose(file);

		}

        // robot->leftClickPosはマウス左ボタンのクリックにより地図を移動できるので、その分を補正している
        //robot->waypoint[i].longitude = map->pixToLon((robot->rightClickPos.x
        //                               - (int) (0.5 * WINDOW_WIDTH) + robot->leftClickPos.x - offset_x)/map->getScale());
        //robot->waypoint[i].latitude   = map->pixToLat((robot->rightClickPos.y
        //                                - (int) (0.5 * WINDOW_HEIGHT) + robot->leftClickPos.y - offset_y)/map->getScale());
        //robot->waypoint[i].longitude = map->pixToLon((robot->rightClickPos.x
        //                                - robot->draw_x0 - offset_x)/map->getScale());
        //robot->waypoint[i].latitude   = map->pixToLat((robot->rightClickPos.y
        //                               - robot->draw_y0 - offset_y)/map->getScale());
        robot->waypoint[i].longitude = map->pixToLon((robot->rightClickPos.x
                                        - robot->draw_x0 - offset_x));
        robot->waypoint[i].latitude   = map->pixToLat((robot->rightClickPos.y
                                        - robot->draw_y0 - offset_y));
        robot->waypoint[i].x = map->lonToMeter(robot->waypoint[i].longitude - robot->waypoint[START_WAYPOINT].longitude);
        robot->waypoint[i].y = map->latToMeter(robot->waypoint[i].latitude  - robot->waypoint[START_WAYPOINT].latitude);

        // robot->waypoint[i].offset = offset;
        robot->waypoint[i].pose       = (double) pose;
    }
}

//! 経由点設定ボタン
void MainWindow::on_wpRadioOnBtn_clicked()
{
    int    wp_no = 0;
    // double wp_offset = 0.0;
    double wp_pose = 0;

    wp_no =   ui->wpSpinBox->text().toInt();
    // wp_offset = ui->wpDoubleSpinBox->text().toDouble();
    wp_pose = ui->wpSpinBox2->text().toInt();
    setWayPoint4(wp_no, wp_pose);
}

