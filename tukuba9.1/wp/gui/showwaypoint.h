#ifndef SHOWWAYPOINT_H
#define SHOWWAYPOINT_H

#include <QDialog>

namespace Ui {
    class ShowWaypointClass;
}

class ShowWaypointClass : public QDialog
{
    Q_OBJECT

public:
    ShowWaypointClass(QWidget *parent = 0);
    //ShowWaypointClass(QWidget *parent = 0);
    // CoordinateSetter coordinateSetter;
    ~ShowWaypointClass();

private:
    Ui::ShowWaypointClass *ui;

    double lonToMeter(double lon);
    double latToMeter(double lat);


private slots:
    void on_pushButton_clicked();
};

#endif // SHOWWAYPOINT_H
