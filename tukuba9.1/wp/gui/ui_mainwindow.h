/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGroupBox>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QRadioButton>
#include <QtGui/QScrollArea>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAddWP;
    QWidget *centralWidget;
    QGroupBox *infoBox;
    QLabel *label_2;
    QLabel *label_3;
    QRadioButton *wpRadioOnBtn;
    QRadioButton *wpRadioOffBtn;
    QLabel *label_5;
    QSpinBox *wpSpinBox;
    QLabel *label_6;
    QSpinBox *wpSpinBox2;
    QScrollArea *scrollArea;
    QWidget *mapArea2;
    QMenuBar *menuBar;
    QToolBar *toolBar;
    QStatusBar *statusBar;
    QButtonGroup *buttonGroup_2;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1216, 769);
        QFont font;
        font.setPointSize(10);
        MainWindow->setFont(font);
        actionAddWP = new QAction(MainWindow);
        actionAddWP->setObjectName(QString::fromUtf8("actionAddWP"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        infoBox = new QGroupBox(centralWidget);
        infoBox->setObjectName(QString::fromUtf8("infoBox"));
        infoBox->setEnabled(true);
        infoBox->setGeometry(QRect(0, 0, 91, 381));
        QFont font1;
        font1.setFamily(QString::fromUtf8("AlArabiya"));
        font1.setPointSize(12);
        font1.setKerning(true);
        infoBox->setFont(font1);
        label_2 = new QLabel(infoBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(-80, 290, 41, 20));
        label_2->setFont(font);
        label_3 = new QLabel(infoBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 10, 81, 21));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Takao\343\202\264\343\202\267\343\203\203\343\202\257"));
        font2.setPointSize(14);
        font2.setBold(false);
        font2.setWeight(50);
        label_3->setFont(font2);
        wpRadioOnBtn = new QRadioButton(infoBox);
        buttonGroup_2 = new QButtonGroup(MainWindow);
        buttonGroup_2->setObjectName(QString::fromUtf8("buttonGroup_2"));
        buttonGroup_2->addButton(wpRadioOnBtn);
        wpRadioOnBtn->setObjectName(QString::fromUtf8("wpRadioOnBtn"));
        wpRadioOnBtn->setGeometry(QRect(10, 30, 51, 19));
        wpRadioOnBtn->setFont(font);
        wpRadioOffBtn = new QRadioButton(infoBox);
        buttonGroup_2->addButton(wpRadioOffBtn);
        wpRadioOffBtn->setObjectName(QString::fromUtf8("wpRadioOffBtn"));
        wpRadioOffBtn->setGeometry(QRect(10, 50, 61, 19));
        wpRadioOffBtn->setFont(font);
        wpRadioOffBtn->setChecked(true);
        label_5 = new QLabel(infoBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 80, 61, 20));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Takao P\343\202\264\343\202\267\343\203\203\343\202\257"));
        font3.setPointSize(12);
        label_5->setFont(font3);
        wpSpinBox = new QSpinBox(infoBox);
        wpSpinBox->setObjectName(QString::fromUtf8("wpSpinBox"));
        wpSpinBox->setGeometry(QRect(10, 100, 71, 31));
        QFont font4;
        font4.setPointSize(12);
        wpSpinBox->setFont(font4);
        wpSpinBox->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wpSpinBox->setMaximum(200);
        label_6 = new QLabel(infoBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 140, 61, 20));
        label_6->setFont(font3);
        wpSpinBox2 = new QSpinBox(infoBox);
        wpSpinBox2->setObjectName(QString::fromUtf8("wpSpinBox2"));
        wpSpinBox2->setGeometry(QRect(10, 170, 71, 31));
        wpSpinBox2->setFont(font4);
        wpSpinBox2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        wpSpinBox2->setMaximum(359);
        scrollArea = new QScrollArea(centralWidget);
        scrollArea->setObjectName(QString::fromUtf8("scrollArea"));
        scrollArea->setGeometry(QRect(90, 30, 1131, 700));
        scrollArea->setFont(font);
        scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
        scrollArea->setWidgetResizable(true);
        mapArea2 = new QWidget();
        mapArea2->setObjectName(QString::fromUtf8("mapArea2"));
        mapArea2->setGeometry(QRect(0, 0, 1129, 698));
        scrollArea->setWidget(mapArea2);
        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1216, 20));
        MainWindow->setMenuBar(menuBar);
        toolBar = new QToolBar(MainWindow);
        toolBar->setObjectName(QString::fromUtf8("toolBar"));
        toolBar->setMovable(false);
        toolBar->setAllowedAreas(Qt::TopToolBarArea);
        toolBar->setToolButtonStyle(Qt::ToolButtonTextBesideIcon);
        toolBar->setFloatable(false);
        MainWindow->addToolBar(Qt::TopToolBarArea, toolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", 0, QApplication::UnicodeUTF8));
        actionAddWP->setText(QApplication::translate("MainWindow", "addWP", 0, QApplication::UnicodeUTF8));
        infoBox->setTitle(QString());
        label_2->setText(QApplication::translate("MainWindow", "0", 0, QApplication::UnicodeUTF8));
        label_3->setText(QApplication::translate("MainWindow", "Set", 0, QApplication::UnicodeUTF8));
        wpRadioOnBtn->setText(QApplication::translate("MainWindow", "ON", 0, QApplication::UnicodeUTF8));
        wpRadioOffBtn->setText(QApplication::translate("MainWindow", "OFF", 0, QApplication::UnicodeUTF8));
        label_5->setText(QApplication::translate("MainWindow", "WP No.", 0, QApplication::UnicodeUTF8));
        label_6->setText(QApplication::translate("MainWindow", "Pose [\302\260]", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
