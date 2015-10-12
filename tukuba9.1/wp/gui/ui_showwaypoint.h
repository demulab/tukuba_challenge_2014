/********************************************************************************
** Form generated from reading UI file 'showwaypoint.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SHOWWAYPOINT_H
#define UI_SHOWWAYPOINT_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QHeaderView>
#include <QtGui/QPushButton>
#include <QtGui/QTextBrowser>

QT_BEGIN_NAMESPACE

class Ui_ShowWaypointClass
{
public:
    QTextBrowser *textBrowser;
    QPushButton *pushButton;

    void setupUi(QDialog *ShowWaypointClass)
    {
        if (ShowWaypointClass->objectName().isEmpty())
            ShowWaypointClass->setObjectName(QString::fromUtf8("ShowWaypointClass"));
        ShowWaypointClass->resize(320, 674);
        textBrowser = new QTextBrowser(ShowWaypointClass);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(10, 10, 301, 621));
        pushButton = new QPushButton(ShowWaypointClass);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(220, 640, 91, 27));

        retranslateUi(ShowWaypointClass);

        QMetaObject::connectSlotsByName(ShowWaypointClass);
    } // setupUi

    void retranslateUi(QDialog *ShowWaypointClass)
    {
        ShowWaypointClass->setWindowTitle(QApplication::translate("ShowWaypointClass", "Waypoints", 0, QApplication::UnicodeUTF8));
        pushButton->setText(QApplication::translate("ShowWaypointClass", "\351\226\211\343\201\230\343\202\213", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class ShowWaypointClass: public Ui_ShowWaypointClass {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SHOWWAYPOINT_H
