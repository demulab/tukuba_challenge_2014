#include <QFile>
#include <QTextStream>
#include <iostream>
#include <cmath>

#include "../robot/robot.h"
#include "gui.h"
#include "showwaypoint.h"
#include "ui_showwaypoint.h"
#include "../include/MyDefine.h"

extern RobotClass  *robot;
extern GuiClass    *gui;

using namespace std;

//! コンストラクタ
ShowWaypointClass::ShowWaypointClass(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ShowWaypointClass)
{
    ui->setupUi(this);

    //QFile file(KIT_WAYPOINTS_FILE);
    //QFile file("./waypoints/KIT_WAY_POINTS0.txt");

    /* if (!file.open(QIODevice::ReadOnly))
    {
        cerr << " cannot open file for reading: "
        << qPrintable(file.errorString()) << endl;
        return;
    }*/


    /* QTextStream in(&file);
    int i = 0;
    while (!in.atEnd())
    {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() >= 3)
        {
            int no = fields.takeFirst().toDouble();
            robot->waypoint[i].latitude  = fields.takeFirst().toDouble();
            robot->waypoint[i].longitude = fields.takeFirst().toDouble();
            i++;
        }
    } */


    /* if (!file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        std::cout << "can not open file." << std::endl;
        // return 0;
    } */

    //ui->textBrowser->insertPlainText("No.       X [m]         Y[m]      Offset[m]\n");
    /* int i = 0;
    QTextStream in( &file );
    while (!in.atEnd()) {
        QString line = in.readLine();
        QStringList fields = line.split(',');

        if (fields.size() >= 4)
        {
            ui->textBrowser->insertPlainText(fields.takeFirst());
            ui->textBrowser->insertPlainText(":");
            ui->textBrowser->insertPlainText(fields.takeFirst());
            ui->textBrowser->insertPlainText(" ");
            ui->textBrowser->insertPlainText(fields.takeFirst());
            ui->textBrowser->insertPlainText("\n");
            i++;
        }
     } */

    ui->textBrowser->insertPlainText("No.     X [m]     Y[m]     Pose[deg]\n");
    // ウェイポイントの表示
    for (int i = 0; i < WAYPOINTS_NUM; i++)
    {
         QString s1 = QString::number(i);

         // メートル表示
         double tmpx = lonToMeter(robot->waypoint[i].longitude - robot->waypoint[START_WAYPOINT].longitude);
         double tmpy = latToMeter(robot->waypoint[i].latitude - robot->waypoint[START_WAYPOINT].latitude);
         double offset = robot->waypoint[i].offset;
         double pose   = robot->waypoint[i].pose;
         if (fabs(tmpx) > 4000) tmpx = NAN;
         if (fabs(tmpy) > 4000) tmpy = NAN;

         QString s2 = " "  + QString::number(tmpx, 'f',10);
         QString s3 = " "  + QString::number(tmpy, 'f',10);
         QString s4 = " "  + QString::number(pose, 'f',10) + "\n";
         QString s5 = QString("%1 %2 %3 %4\n").arg(i).arg(tmpx,10,'f',2).arg(tmpy,10,'f',2).arg(pose,10,'f',2);

         ui->textBrowser->insertPlainText(s5);


     }
}

//! デストラクタ
ShowWaypointClass::~ShowWaypointClass()
{
    delete ui;
}

//! 経度をメートルに変換
double ShowWaypointClass::lonToMeter(double lon)
{
    if (robot->tukuba) return lon * TUKUBA_LON_TO_METER;
    else               return lon * KIT_LON_TO_METER;
}

//! 緯度をメートルに変換
double ShowWaypointClass::latToMeter(double lat)
{
    if (robot->tukuba) return lat * TUKUBA_LAT_TO_METER;
    else               return lat * KIT_LAT_TO_METER;
}

void ShowWaypointClass::on_pushButton_clicked()
{
    close();
}
