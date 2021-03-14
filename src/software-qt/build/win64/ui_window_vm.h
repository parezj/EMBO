/********************************************************************************
** Form generated from reading UI file 'window_vm.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_VM_H
#define UI_WINDOW_VM_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QDoubleSpinBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "lib/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_WindowVm
{
public:
    QAction *actionAbout;
    QAction *actionStart;
    QAction *actionStop;
    QAction *actionFolder;
    QAction *actionFormat;
    QAction *actionLines;
    QAction *actionPoints;
    QAction *actionLinear;
    QAction *actionSinc;
    QAction *actionCSV;
    QAction *actionTXT_Tabs;
    QAction *actionMAT;
    QAction *actionMax;
    QAction *actionMin;
    QAction *actionAverage;
    QAction *actionReset;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_rightPanel;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_ch1;
    QTextBrowser *textBrowser_ch1;
    QDoubleSpinBox *doubleSpinBox_gain1;
    QLabel *label_7;
    QPushButton *pushButton_disable1;
    QPushButton *pushButton_enable1;
    QLabel *label_ch1;
    QGroupBox *groupBox_ch2;
    QTextBrowser *textBrowser_ch2;
    QDoubleSpinBox *doubleSpinBox_gain2;
    QLabel *label_6;
    QPushButton *pushButton_disable2;
    QPushButton *pushButton_enable2;
    QLabel *label_ch2;
    QGroupBox *groupBox_ch3;
    QTextBrowser *textBrowser_ch3;
    QDoubleSpinBox *doubleSpinBox_gain3;
    QLabel *label_5;
    QPushButton *pushButton_disable3;
    QPushButton *pushButton_enable3;
    QLabel *label_ch3;
    QGroupBox *groupBox_ch4;
    QTextBrowser *textBrowser_ch4;
    QDoubleSpinBox *doubleSpinBox_gain4;
    QLabel *label_4;
    QPushButton *pushButton_enable4;
    QPushButton *pushButton_disable4;
    QLabel *label_ch4;
    QGroupBox *groupBox_settigns;
    QLabel *label_3;
    QDial *dial_display;
    QSpinBox *spinBox_display;
    QLabel *label_dial4;
    QSpinBox *spinBox_average;
    QDial *dial_average;
    QLabel *label_2;
    QLabel *label_dial3;
    QPushButton *pushButton_disable;
    QPushButton *pushButton_enable;
    QLabel *label_13;
    QSpacerItem *verticalSpacer_4;
    QCustomPlot *customPlot;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QMenu *menuRecord;
    QMenu *menuFormat;
    QMenu *menuView;
    QMenu *menuInterpolation;
    QMenu *menuMeasure;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowVm)
    {
        if (WindowVm->objectName().isEmpty())
            WindowVm->setObjectName(QString::fromUtf8("WindowVm"));
        WindowVm->resize(1067, 649);
        WindowVm->setMinimumSize(QSize(803, 0));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        WindowVm->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowVm->setWindowIcon(icon);
        actionAbout = new QAction(WindowVm);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon1);
        actionAbout->setFont(font);
        actionStart = new QAction(WindowVm);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionStart->setFont(font);
        actionStop = new QAction(WindowVm);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionStop->setFont(font);
        actionFolder = new QAction(WindowVm);
        actionFolder->setObjectName(QString::fromUtf8("actionFolder"));
        actionFolder->setFont(font);
        actionFormat = new QAction(WindowVm);
        actionFormat->setObjectName(QString::fromUtf8("actionFormat"));
        actionLines = new QAction(WindowVm);
        actionLines->setObjectName(QString::fromUtf8("actionLines"));
        actionLines->setCheckable(true);
        actionLines->setChecked(true);
        actionLines->setFont(font);
        actionPoints = new QAction(WindowVm);
        actionPoints->setObjectName(QString::fromUtf8("actionPoints"));
        actionPoints->setCheckable(true);
        actionPoints->setFont(font);
        actionLinear = new QAction(WindowVm);
        actionLinear->setObjectName(QString::fromUtf8("actionLinear"));
        actionLinear->setCheckable(true);
        actionLinear->setChecked(true);
        actionLinear->setFont(font);
        actionSinc = new QAction(WindowVm);
        actionSinc->setObjectName(QString::fromUtf8("actionSinc"));
        actionSinc->setCheckable(true);
        actionSinc->setEnabled(false);
        actionSinc->setFont(font);
        actionCSV = new QAction(WindowVm);
        actionCSV->setObjectName(QString::fromUtf8("actionCSV"));
        actionCSV->setCheckable(true);
        actionCSV->setChecked(true);
        actionCSV->setFont(font);
        actionTXT_Tabs = new QAction(WindowVm);
        actionTXT_Tabs->setObjectName(QString::fromUtf8("actionTXT_Tabs"));
        actionTXT_Tabs->setCheckable(true);
        actionTXT_Tabs->setFont(font);
        actionMAT = new QAction(WindowVm);
        actionMAT->setObjectName(QString::fromUtf8("actionMAT"));
        actionMAT->setCheckable(true);
        actionMAT->setFont(font);
        actionMax = new QAction(WindowVm);
        actionMax->setObjectName(QString::fromUtf8("actionMax"));
        actionMax->setCheckable(true);
        actionMin = new QAction(WindowVm);
        actionMin->setObjectName(QString::fromUtf8("actionMin"));
        actionMin->setCheckable(true);
        actionAverage = new QAction(WindowVm);
        actionAverage->setObjectName(QString::fromUtf8("actionAverage"));
        actionAverage->setCheckable(true);
        actionReset = new QAction(WindowVm);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        centralwidget = new QWidget(WindowVm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        groupBox_rightPanel = new QGroupBox(centralwidget);
        groupBox_rightPanel->setObjectName(QString::fromUtf8("groupBox_rightPanel"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(groupBox_rightPanel->sizePolicy().hasHeightForWidth());
        groupBox_rightPanel->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        groupBox_rightPanel->setFont(font1);
        groupBox_rightPanel->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.0em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        verticalLayout_2 = new QVBoxLayout(groupBox_rightPanel);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_ch1 = new QGroupBox(groupBox_rightPanel);
        groupBox_ch1->setObjectName(QString::fromUtf8("groupBox_ch1"));
        groupBox_ch1->setMinimumSize(QSize(370, 100));
        groupBox_ch1->setMaximumSize(QSize(16777215, 150));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto Medium"));
        font2.setPointSize(11);
        groupBox_ch1->setFont(font2);
        groupBox_ch1->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 1px solid rgb(150,150,150); border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        textBrowser_ch1 = new QTextBrowser(groupBox_ch1);
        textBrowser_ch1->setObjectName(QString::fromUtf8("textBrowser_ch1"));
        textBrowser_ch1->setEnabled(true);
        textBrowser_ch1->setGeometry(QRect(9, 26, 225, 65));
        sizePolicy.setHeightForWidth(textBrowser_ch1->sizePolicy().hasHeightForWidth());
        textBrowser_ch1->setSizePolicy(sizePolicy);
        textBrowser_ch1->setMaximumSize(QSize(225, 65));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Roboto Mono Medium"));
        font3.setPointSize(30);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(62);
        textBrowser_ch1->setFont(font3);
        textBrowser_ch1->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch1->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: transparent;\n"
"	border-color: transparent; border-width: 1px solid gray; border-style:inset; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        doubleSpinBox_gain1 = new QDoubleSpinBox(groupBox_ch1);
        doubleSpinBox_gain1->setObjectName(QString::fromUtf8("doubleSpinBox_gain1"));
        doubleSpinBox_gain1->setGeometry(QRect(240, 61, 121, 30));
        doubleSpinBox_gain1->setMinimumSize(QSize(121, 0));
        doubleSpinBox_gain1->setMaximumSize(QSize(120, 16777215));
        doubleSpinBox_gain1->setStyleSheet(QString::fromUtf8("QDoubleSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:5px;\n"
"				   text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;  }\n"
"\n"
"QDoubleSpinBox::up-button { height:22px; width: 30px; border: 0px;\n"
"									 image: url(:/main/resources/img/arrow_up4.png); }\n"
"\n"
"QDoubleSpinBox::down-button { height:22px; width: 30px; border: 0px;\n"
"										  image: url(:/main/resources/img/arrow_down4.png); }\n"
"\n"
"QDoubleSpinBox::up-button:hover { \n"
"	image: url(:/main/resources/img/arrow_up4b.png);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button:hover {\n"
"	image: url(:/main/resources/img/arrow_down4b.png);\n"
" }\n"
"\n"
"QDoubleSpinBox:disabled { background-color: rgba(240,240,240, 1.0); border: 1px transparent; border-radius:5px;\n"
"                                          border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px;\n"
"                                          text-align:right;fon"
                        "t-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QDoubleSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
"\n"
"QDoubleSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_down2.png); }\n"
""));
        doubleSpinBox_gain1->setWrapping(false);
        doubleSpinBox_gain1->setFrame(true);
        doubleSpinBox_gain1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_gain1->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_gain1->setAccelerated(false);
        doubleSpinBox_gain1->setKeyboardTracking(false);
        doubleSpinBox_gain1->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_gain1->setDecimals(2);
        doubleSpinBox_gain1->setMinimum(0.010000000000000);
        doubleSpinBox_gain1->setValue(1.000000000000000);
        label_7 = new QLabel(groupBox_ch1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(246, 65, 45, 23));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto Light"));
        font4.setPointSize(14);
        font4.setBold(false);
        font4.setWeight(50);
        label_7->setFont(font4);
        pushButton_disable1 = new QPushButton(groupBox_ch1);
        pushButton_disable1->setObjectName(QString::fromUtf8("pushButton_disable1"));
        pushButton_disable1->setGeometry(QRect(240, 26, 121, 30));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Roboto"));
        font5.setPointSize(13);
        pushButton_disable1->setFont(font5);
        pushButton_disable1->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Disabled, QIcon::Off);
        pushButton_disable1->setIcon(icon2);
        pushButton_disable1->setIconSize(QSize(23, 22));
        pushButton_enable1 = new QPushButton(groupBox_ch1);
        pushButton_enable1->setObjectName(QString::fromUtf8("pushButton_enable1"));
        pushButton_enable1->setGeometry(QRect(240, 26, 121, 30));
        pushButton_enable1->setFont(font5);
        pushButton_enable1->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/main/resources/img/power-off-gray2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_enable1->setIcon(icon3);
        pushButton_enable1->setIconSize(QSize(23, 22));
        label_ch1 = new QLabel(groupBox_ch1);
        label_ch1->setObjectName(QString::fromUtf8("label_ch1"));
        label_ch1->setGeometry(QRect(10, 8, 221, 16));
        label_ch1->setFont(font2);
        textBrowser_ch1->raise();
        doubleSpinBox_gain1->raise();
        label_7->raise();
        pushButton_enable1->raise();
        pushButton_disable1->raise();
        label_ch1->raise();

        verticalLayout_2->addWidget(groupBox_ch1);

        groupBox_ch2 = new QGroupBox(groupBox_rightPanel);
        groupBox_ch2->setObjectName(QString::fromUtf8("groupBox_ch2"));
        groupBox_ch2->setMinimumSize(QSize(370, 100));
        groupBox_ch2->setMaximumSize(QSize(16777215, 150));
        groupBox_ch2->setFont(font2);
        groupBox_ch2->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 1px solid rgb(150,150,150); border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        textBrowser_ch2 = new QTextBrowser(groupBox_ch2);
        textBrowser_ch2->setObjectName(QString::fromUtf8("textBrowser_ch2"));
        textBrowser_ch2->setEnabled(true);
        textBrowser_ch2->setGeometry(QRect(9, 26, 225, 65));
        sizePolicy.setHeightForWidth(textBrowser_ch2->sizePolicy().hasHeightForWidth());
        textBrowser_ch2->setSizePolicy(sizePolicy);
        textBrowser_ch2->setMaximumSize(QSize(225, 65));
        textBrowser_ch2->setFont(font3);
        textBrowser_ch2->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch2->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: transparent;\n"
"	border-color: transparent; border-width: 1px solid gray; border-style:inset; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        doubleSpinBox_gain2 = new QDoubleSpinBox(groupBox_ch2);
        doubleSpinBox_gain2->setObjectName(QString::fromUtf8("doubleSpinBox_gain2"));
        doubleSpinBox_gain2->setGeometry(QRect(240, 61, 121, 30));
        doubleSpinBox_gain2->setMinimumSize(QSize(121, 0));
        doubleSpinBox_gain2->setMaximumSize(QSize(120, 16777215));
        doubleSpinBox_gain2->setStyleSheet(QString::fromUtf8("QDoubleSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:5px;\n"
"				   text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;  }\n"
"\n"
"QDoubleSpinBox::up-button { height:22px; width: 30px; border: 0px;\n"
"									 image: url(:/main/resources/img/arrow_up4.png); }\n"
"\n"
"QDoubleSpinBox::down-button { height:22px; width: 30px; border: 0px;\n"
"										  image: url(:/main/resources/img/arrow_down4.png); }\n"
"\n"
"QDoubleSpinBox::up-button:hover { \n"
"	image: url(:/main/resources/img/arrow_up4b.png);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button:hover {\n"
"	image: url(:/main/resources/img/arrow_down4b.png);\n"
" }\n"
"\n"
"QDoubleSpinBox:disabled { background-color: rgba(240,240,240, 1.0); border: 1px transparent; border-radius:5px;\n"
"                                          border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px;\n"
"                                          text-align:right;fon"
                        "t-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QDoubleSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
"\n"
"QDoubleSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_down2.png); }\n"
""));
        doubleSpinBox_gain2->setWrapping(false);
        doubleSpinBox_gain2->setFrame(true);
        doubleSpinBox_gain2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_gain2->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_gain2->setAccelerated(false);
        doubleSpinBox_gain2->setKeyboardTracking(false);
        doubleSpinBox_gain2->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_gain2->setDecimals(2);
        doubleSpinBox_gain2->setMinimum(0.010000000000000);
        doubleSpinBox_gain2->setValue(1.000000000000000);
        label_6 = new QLabel(groupBox_ch2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(246, 65, 45, 23));
        label_6->setFont(font4);
        pushButton_disable2 = new QPushButton(groupBox_ch2);
        pushButton_disable2->setObjectName(QString::fromUtf8("pushButton_disable2"));
        pushButton_disable2->setGeometry(QRect(240, 26, 121, 30));
        pushButton_disable2->setFont(font5);
        pushButton_disable2->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        pushButton_disable2->setIcon(icon2);
        pushButton_disable2->setIconSize(QSize(23, 22));
        pushButton_enable2 = new QPushButton(groupBox_ch2);
        pushButton_enable2->setObjectName(QString::fromUtf8("pushButton_enable2"));
        pushButton_enable2->setGeometry(QRect(240, 26, 121, 30));
        pushButton_enable2->setFont(font5);
        pushButton_enable2->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        pushButton_enable2->setIcon(icon3);
        pushButton_enable2->setIconSize(QSize(23, 22));
        label_ch2 = new QLabel(groupBox_ch2);
        label_ch2->setObjectName(QString::fromUtf8("label_ch2"));
        label_ch2->setGeometry(QRect(10, 8, 221, 16));
        label_ch2->setFont(font2);
        textBrowser_ch2->raise();
        doubleSpinBox_gain2->raise();
        label_6->raise();
        pushButton_enable2->raise();
        pushButton_disable2->raise();
        label_ch2->raise();

        verticalLayout_2->addWidget(groupBox_ch2);

        groupBox_ch3 = new QGroupBox(groupBox_rightPanel);
        groupBox_ch3->setObjectName(QString::fromUtf8("groupBox_ch3"));
        groupBox_ch3->setMinimumSize(QSize(370, 100));
        groupBox_ch3->setMaximumSize(QSize(16777215, 150));
        groupBox_ch3->setFont(font2);
        groupBox_ch3->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 1px solid rgb(150,150,150); border-radius: 5px;  margin-top: 0.5em;}; \n"
""));
        textBrowser_ch3 = new QTextBrowser(groupBox_ch3);
        textBrowser_ch3->setObjectName(QString::fromUtf8("textBrowser_ch3"));
        textBrowser_ch3->setEnabled(true);
        textBrowser_ch3->setGeometry(QRect(9, 26, 225, 65));
        sizePolicy.setHeightForWidth(textBrowser_ch3->sizePolicy().hasHeightForWidth());
        textBrowser_ch3->setSizePolicy(sizePolicy);
        textBrowser_ch3->setMaximumSize(QSize(225, 65));
        textBrowser_ch3->setFont(font3);
        textBrowser_ch3->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch3->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: transparent;\n"
"	border-color: transparent; border-width: 1px solid gray; border-style:inset; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        doubleSpinBox_gain3 = new QDoubleSpinBox(groupBox_ch3);
        doubleSpinBox_gain3->setObjectName(QString::fromUtf8("doubleSpinBox_gain3"));
        doubleSpinBox_gain3->setGeometry(QRect(240, 61, 121, 30));
        doubleSpinBox_gain3->setMinimumSize(QSize(121, 0));
        doubleSpinBox_gain3->setMaximumSize(QSize(120, 16777215));
        doubleSpinBox_gain3->setStyleSheet(QString::fromUtf8("QDoubleSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:5px;\n"
"				   text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;  }\n"
"\n"
"QDoubleSpinBox::up-button { height:22px; width: 30px; border: 0px;\n"
"									 image: url(:/main/resources/img/arrow_up4.png); }\n"
"\n"
"QDoubleSpinBox::down-button { height:22px; width: 30px; border: 0px;\n"
"										  image: url(:/main/resources/img/arrow_down4.png); }\n"
"\n"
"QDoubleSpinBox::up-button:hover { \n"
"	image: url(:/main/resources/img/arrow_up4b.png);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button:hover {\n"
"	image: url(:/main/resources/img/arrow_down4b.png);\n"
" }\n"
"\n"
"QDoubleSpinBox:disabled { background-color: rgba(240,240,240, 1.0); border: 1px transparent; border-radius:5px;\n"
"                                          border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px;\n"
"                                          text-align:right;fon"
                        "t-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QDoubleSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
"\n"
"QDoubleSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_down2.png); }\n"
""));
        doubleSpinBox_gain3->setWrapping(false);
        doubleSpinBox_gain3->setFrame(true);
        doubleSpinBox_gain3->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_gain3->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_gain3->setAccelerated(false);
        doubleSpinBox_gain3->setKeyboardTracking(false);
        doubleSpinBox_gain3->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_gain3->setDecimals(2);
        doubleSpinBox_gain3->setMinimum(0.010000000000000);
        doubleSpinBox_gain3->setValue(1.000000000000000);
        label_5 = new QLabel(groupBox_ch3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(246, 65, 45, 23));
        label_5->setFont(font4);
        pushButton_disable3 = new QPushButton(groupBox_ch3);
        pushButton_disable3->setObjectName(QString::fromUtf8("pushButton_disable3"));
        pushButton_disable3->setGeometry(QRect(240, 26, 121, 30));
        pushButton_disable3->setFont(font5);
        pushButton_disable3->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        pushButton_disable3->setIcon(icon2);
        pushButton_disable3->setIconSize(QSize(23, 22));
        pushButton_enable3 = new QPushButton(groupBox_ch3);
        pushButton_enable3->setObjectName(QString::fromUtf8("pushButton_enable3"));
        pushButton_enable3->setGeometry(QRect(240, 26, 121, 30));
        pushButton_enable3->setFont(font5);
        pushButton_enable3->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        pushButton_enable3->setIcon(icon3);
        pushButton_enable3->setIconSize(QSize(23, 22));
        label_ch3 = new QLabel(groupBox_ch3);
        label_ch3->setObjectName(QString::fromUtf8("label_ch3"));
        label_ch3->setGeometry(QRect(10, 8, 221, 16));
        label_ch3->setFont(font2);
        textBrowser_ch3->raise();
        doubleSpinBox_gain3->raise();
        label_5->raise();
        pushButton_enable3->raise();
        pushButton_disable3->raise();
        label_ch3->raise();

        verticalLayout_2->addWidget(groupBox_ch3);

        groupBox_ch4 = new QGroupBox(groupBox_rightPanel);
        groupBox_ch4->setObjectName(QString::fromUtf8("groupBox_ch4"));
        groupBox_ch4->setMinimumSize(QSize(370, 100));
        groupBox_ch4->setMaximumSize(QSize(16777215, 150));
        groupBox_ch4->setFont(font2);
        groupBox_ch4->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 1px solid rgb(150,150,150); border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        textBrowser_ch4 = new QTextBrowser(groupBox_ch4);
        textBrowser_ch4->setObjectName(QString::fromUtf8("textBrowser_ch4"));
        textBrowser_ch4->setEnabled(true);
        textBrowser_ch4->setGeometry(QRect(9, 26, 225, 65));
        sizePolicy.setHeightForWidth(textBrowser_ch4->sizePolicy().hasHeightForWidth());
        textBrowser_ch4->setSizePolicy(sizePolicy);
        textBrowser_ch4->setMaximumSize(QSize(225, 65));
        textBrowser_ch4->setFont(font3);
        textBrowser_ch4->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch4->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: transparent;\n"
"	border-color: transparent; border-width: 1px solid gray; border-style:inset; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        doubleSpinBox_gain4 = new QDoubleSpinBox(groupBox_ch4);
        doubleSpinBox_gain4->setObjectName(QString::fromUtf8("doubleSpinBox_gain4"));
        doubleSpinBox_gain4->setGeometry(QRect(240, 61, 121, 30));
        doubleSpinBox_gain4->setMinimumSize(QSize(121, 0));
        doubleSpinBox_gain4->setMaximumSize(QSize(120, 16777215));
        doubleSpinBox_gain4->setStyleSheet(QString::fromUtf8("QDoubleSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:5px;\n"
"				   text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;  }\n"
"\n"
"QDoubleSpinBox::up-button { height:22px; width: 30px; border: 0px;\n"
"									 image: url(:/main/resources/img/arrow_up4.png); }\n"
"\n"
"QDoubleSpinBox::down-button { height:22px; width: 30px; border: 0px;\n"
"										  image: url(:/main/resources/img/arrow_down4.png); }\n"
"\n"
"QDoubleSpinBox::up-button:hover { \n"
"	image: url(:/main/resources/img/arrow_up4b.png);\n"
"}\n"
"\n"
"QDoubleSpinBox::down-button:hover {\n"
"	image: url(:/main/resources/img/arrow_down4b.png);\n"
" }\n"
"\n"
"QDoubleSpinBox:disabled { background-color: rgba(240,240,240, 1.0); border: 1px transparent; border-radius:5px;\n"
"                                          border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px;\n"
"                                          text-align:right;fon"
                        "t-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QDoubleSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
"\n"
"QDoubleSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_down2.png); }\n"
""));
        doubleSpinBox_gain4->setWrapping(false);
        doubleSpinBox_gain4->setFrame(true);
        doubleSpinBox_gain4->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        doubleSpinBox_gain4->setButtonSymbols(QAbstractSpinBox::NoButtons);
        doubleSpinBox_gain4->setAccelerated(false);
        doubleSpinBox_gain4->setKeyboardTracking(false);
        doubleSpinBox_gain4->setProperty("showGroupSeparator", QVariant(false));
        doubleSpinBox_gain4->setDecimals(2);
        doubleSpinBox_gain4->setMinimum(0.010000000000000);
        doubleSpinBox_gain4->setValue(1.000000000000000);
        label_4 = new QLabel(groupBox_ch4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(246, 65, 45, 23));
        label_4->setFont(font4);
        pushButton_enable4 = new QPushButton(groupBox_ch4);
        pushButton_enable4->setObjectName(QString::fromUtf8("pushButton_enable4"));
        pushButton_enable4->setGeometry(QRect(240, 26, 121, 30));
        pushButton_enable4->setFont(font5);
        pushButton_enable4->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        pushButton_enable4->setIcon(icon3);
        pushButton_enable4->setIconSize(QSize(23, 22));
        pushButton_disable4 = new QPushButton(groupBox_ch4);
        pushButton_disable4->setObjectName(QString::fromUtf8("pushButton_disable4"));
        pushButton_disable4->setGeometry(QRect(240, 26, 121, 30));
        pushButton_disable4->setFont(font5);
        pushButton_disable4->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        pushButton_disable4->setIcon(icon2);
        pushButton_disable4->setIconSize(QSize(23, 22));
        label_ch4 = new QLabel(groupBox_ch4);
        label_ch4->setObjectName(QString::fromUtf8("label_ch4"));
        label_ch4->setGeometry(QRect(10, 8, 221, 16));
        label_ch4->setFont(font2);

        verticalLayout_2->addWidget(groupBox_ch4);

        groupBox_settigns = new QGroupBox(groupBox_rightPanel);
        groupBox_settigns->setObjectName(QString::fromUtf8("groupBox_settigns"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_settigns->sizePolicy().hasHeightForWidth());
        groupBox_settigns->setSizePolicy(sizePolicy1);
        groupBox_settigns->setMinimumSize(QSize(0, 140));
        groupBox_settigns->setMaximumSize(QSize(16777215, 140));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Roboto Medium"));
        font6.setPointSize(11);
        font6.setBold(false);
        font6.setItalic(false);
        font6.setWeight(50);
        font6.setKerning(true);
        groupBox_settigns->setFont(font6);
        groupBox_settigns->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 1px solid rgb(150,150,150); border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        label_3 = new QLabel(groupBox_settigns);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 95, 141, 21));
        label_3->setFont(font4);
        dial_display = new QDial(groupBox_settigns);
        dial_display->setObjectName(QString::fromUtf8("dial_display"));
        dial_display->setGeometry(QRect(10, 80, 51, 50));
        dial_display->setMinimum(1);
        dial_display->setMaximum(2000);
        dial_display->setValue(100);
        dial_display->setOrientation(Qt::Horizontal);
        dial_display->setInvertedAppearance(false);
        dial_display->setWrapping(false);
        dial_display->setNotchTarget(30.000000000000000);
        dial_display->setNotchesVisible(true);
        spinBox_display = new QSpinBox(groupBox_settigns);
        spinBox_display->setObjectName(QString::fromUtf8("spinBox_display"));
        spinBox_display->setGeometry(QRect(70, 85, 231, 41));
        spinBox_display->setStyleSheet(QString::fromUtf8("QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px;\n"
"				   text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;  }\n"
"\n"
"QSpinBox::up-button { \n"
"	height:22px; \n"
"	width: 30px;\n"
"	border: 0px;\n"
"	image: url(:/main/resources/img/arrow_up4.png);\n"
"}\n"
"\n"
"QSpinBox::down-button {\n"
"	height:22px; \n"
"	width: 30px;\n"
"	border: 0px;\n"
"	image: url(:/main/resources/img/arrow_down4.png);\n"
" }\n"
"\n"
"QSpinBox::up-button:hover { \n"
"	image: url(:/main/resources/img/arrow_up4b.png);\n"
"}\n"
"\n"
"QSpinBox::down-button:hover {\n"
"	image: url(:/main/resources/img/arrow_down4b.png);\n"
" }\n"
"\n"
"QSpinBox:disabled { background-color: rgba(240,240,240, 1.0); border: 1px transparent; border-radius:10px;\n"
"                                          border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px;\n"
"                                          text-align:right;font-family:'Ro"
                        "boto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
"\n"
"QSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_down2.png); }\n"
""));
        spinBox_display->setWrapping(false);
        spinBox_display->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_display->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox_display->setAccelerated(false);
        spinBox_display->setKeyboardTracking(false);
        spinBox_display->setProperty("showGroupSeparator", QVariant(false));
        spinBox_display->setMinimum(1);
        spinBox_display->setMaximum(2000);
        spinBox_display->setValue(300);
        label_dial4 = new QLabel(groupBox_settigns);
        label_dial4->setObjectName(QString::fromUtf8("label_dial4"));
        label_dial4->setGeometry(QRect(10, 80, 51, 50));
        label_dial4->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial4->setScaledContents(false);
        spinBox_average = new QSpinBox(groupBox_settigns);
        spinBox_average->setObjectName(QString::fromUtf8("spinBox_average"));
        spinBox_average->setGeometry(QRect(70, 35, 231, 41));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(spinBox_average->sizePolicy().hasHeightForWidth());
        spinBox_average->setSizePolicy(sizePolicy2);
        spinBox_average->setStyleSheet(QString::fromUtf8("QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px;\n"
"				   text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;  }\n"
"\n"
"QSpinBox::up-button { \n"
"	height:22px; \n"
"	width: 30px;\n"
"	border: 0px;\n"
"	image: url(:/main/resources/img/arrow_up4.png);\n"
"}\n"
"\n"
"QSpinBox::down-button {\n"
"	height:22px; \n"
"	width: 30px;\n"
"	border: 0px;\n"
"	image: url(:/main/resources/img/arrow_down4.png);\n"
" }\n"
"\n"
"QSpinBox::up-button:hover { \n"
"	image: url(:/main/resources/img/arrow_up4b.png);\n"
"}\n"
"\n"
"QSpinBox::down-button:hover {\n"
"	image: url(:/main/resources/img/arrow_down4b.png);\n"
" }\n"
"\n"
"QSpinBox:disabled { background-color: rgba(240,240,240, 1.0); border: 1px transparent; border-radius:10px;\n"
"                                          border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px;\n"
"                                          text-align:right;font-family:'Ro"
                        "boto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
"\n"
"QSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_down2.png); }\n"
""));
        spinBox_average->setWrapping(false);
        spinBox_average->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_average->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox_average->setAccelerated(false);
        spinBox_average->setKeyboardTracking(false);
        spinBox_average->setProperty("showGroupSeparator", QVariant(false));
        spinBox_average->setMinimum(1);
        spinBox_average->setMaximum(300);
        spinBox_average->setValue(1);
        dial_average = new QDial(groupBox_settigns);
        dial_average->setObjectName(QString::fromUtf8("dial_average"));
        dial_average->setGeometry(QRect(10, 30, 51, 50));
        dial_average->setMinimum(1);
        dial_average->setMaximum(300);
        dial_average->setValue(1);
        dial_average->setOrientation(Qt::Horizontal);
        dial_average->setInvertedAppearance(false);
        dial_average->setWrapping(false);
        dial_average->setNotchTarget(15.000000000000000);
        dial_average->setNotchesVisible(true);
        label_2 = new QLabel(groupBox_settigns);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 45, 141, 21));
        label_2->setFont(font4);
        label_dial3 = new QLabel(groupBox_settigns);
        label_dial3->setObjectName(QString::fromUtf8("label_dial3"));
        label_dial3->setGeometry(QRect(10, 30, 51, 50));
        label_dial3->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial3->setScaledContents(false);
        pushButton_disable = new QPushButton(groupBox_settigns);
        pushButton_disable->setObjectName(QString::fromUtf8("pushButton_disable"));
        pushButton_disable->setGeometry(QRect(309, 36, 51, 90));
        pushButton_disable->setFont(font5);
        pushButton_disable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        pushButton_disable->setIcon(icon2);
        pushButton_disable->setIconSize(QSize(23, 22));
        pushButton_enable = new QPushButton(groupBox_settigns);
        pushButton_enable->setObjectName(QString::fromUtf8("pushButton_enable"));
        pushButton_enable->setGeometry(QRect(309, 36, 51, 90));
        pushButton_enable->setFont(font5);
        pushButton_enable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        pushButton_enable->setIcon(icon3);
        pushButton_enable->setIconSize(QSize(23, 22));
        label_13 = new QLabel(groupBox_settigns);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 8, 81, 16));
        label_13->setFont(font2);
        spinBox_display->raise();
        label_3->raise();
        label_dial4->raise();
        dial_display->raise();
        spinBox_average->raise();
        label_2->raise();
        label_dial3->raise();
        dial_average->raise();
        pushButton_enable->raise();
        pushButton_disable->raise();
        label_13->raise();

        verticalLayout_2->addWidget(groupBox_settigns);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);


        gridLayout->addWidget(groupBox_rightPanel, 0, 2, 1, 1);

        customPlot = new QCustomPlot(centralwidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setEnabled(true);
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy3);
        customPlot->setStyleSheet(QString::fromUtf8("background-color: rgb(220,220,220);border: 0px; border-radius: 5px; margin-right:2px;"));

        gridLayout->addWidget(customPlot, 0, 1, 1, 1);

        WindowVm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowVm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1067, 22));
        menubar->setFont(font);
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuHelp->setFont(font);
        menuRecord = new QMenu(menubar);
        menuRecord->setObjectName(QString::fromUtf8("menuRecord"));
        menuRecord->setFont(font);
        menuFormat = new QMenu(menuRecord);
        menuFormat->setObjectName(QString::fromUtf8("menuFormat"));
        menuFormat->setFont(font);
        menuView = new QMenu(menubar);
        menuView->setObjectName(QString::fromUtf8("menuView"));
        menuView->setFont(font);
        menuInterpolation = new QMenu(menuView);
        menuInterpolation->setObjectName(QString::fromUtf8("menuInterpolation"));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Roboto Black"));
        font7.setPointSize(10);
        menuInterpolation->setFont(font7);
        menuMeasure = new QMenu(menubar);
        menuMeasure->setObjectName(QString::fromUtf8("menuMeasure"));
        menuMeasure->setFont(font);
        WindowVm->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowVm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        WindowVm->setStatusBar(statusbar);

        menubar->addAction(menuRecord->menuAction());
        menubar->addAction(menuView->menuAction());
        menubar->addAction(menuMeasure->menuAction());
        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);
        menuRecord->addAction(actionStart);
        menuRecord->addAction(actionStop);
        menuRecord->addSeparator();
        menuRecord->addAction(actionFolder);
        menuRecord->addSeparator();
        menuRecord->addAction(menuFormat->menuAction());
        menuFormat->addAction(actionCSV);
        menuFormat->addAction(actionTXT_Tabs);
        menuFormat->addAction(actionMAT);
        menuView->addAction(actionLines);
        menuView->addAction(actionPoints);
        menuView->addSeparator();
        menuView->addAction(menuInterpolation->menuAction());
        menuView->addSeparator();
        menuInterpolation->addAction(actionLinear);
        menuInterpolation->addAction(actionSinc);
        menuMeasure->addAction(actionMax);
        menuMeasure->addAction(actionMin);
        menuMeasure->addAction(actionAverage);
        menuMeasure->addSeparator();
        menuMeasure->addAction(actionReset);

        retranslateUi(WindowVm);

        QMetaObject::connectSlotsByName(WindowVm);
    } // setupUi

    void retranslateUi(QMainWindow *WindowVm)
    {
        WindowVm->setWindowTitle(QCoreApplication::translate("WindowVm", "EMBO - Voltmeter", nullptr));
        actionAbout->setText(QCoreApplication::translate("WindowVm", "About", nullptr));
        actionStart->setText(QCoreApplication::translate("WindowVm", "Start", nullptr));
        actionStop->setText(QCoreApplication::translate("WindowVm", "Stop", nullptr));
        actionFolder->setText(QCoreApplication::translate("WindowVm", "Folder", nullptr));
        actionFormat->setText(QCoreApplication::translate("WindowVm", "Format", nullptr));
        actionLines->setText(QCoreApplication::translate("WindowVm", "Lines", nullptr));
        actionPoints->setText(QCoreApplication::translate("WindowVm", "Points", nullptr));
        actionLinear->setText(QCoreApplication::translate("WindowVm", "Linear", nullptr));
        actionSinc->setText(QCoreApplication::translate("WindowVm", "Sinc", nullptr));
        actionCSV->setText(QCoreApplication::translate("WindowVm", "CSV", nullptr));
        actionTXT_Tabs->setText(QCoreApplication::translate("WindowVm", "TXT (Tabs)", nullptr));
        actionMAT->setText(QCoreApplication::translate("WindowVm", "MAT", nullptr));
        actionMax->setText(QCoreApplication::translate("WindowVm", "Max", nullptr));
        actionMin->setText(QCoreApplication::translate("WindowVm", "Min", nullptr));
        actionAverage->setText(QCoreApplication::translate("WindowVm", "Average", nullptr));
        actionReset->setText(QCoreApplication::translate("WindowVm", "Reset", nullptr));
        groupBox_rightPanel->setTitle(QString());
        groupBox_ch1->setTitle(QString());
        textBrowser_ch1->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.1240 V</span></p></body></html>", nullptr));
        doubleSpinBox_gain1->setPrefix(QString());
        label_7->setText(QCoreApplication::translate("WindowVm", "Gain:", nullptr));
        pushButton_disable1->setText(QString());
        pushButton_enable1->setText(QString());
        label_ch1->setText(QCoreApplication::translate("WindowVm", "Channel 1", nullptr));
        groupBox_ch2->setTitle(QString());
        textBrowser_ch2->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.1240 V</span></p></body></html>", nullptr));
        doubleSpinBox_gain2->setPrefix(QString());
        label_6->setText(QCoreApplication::translate("WindowVm", "Gain:", nullptr));
        pushButton_disable2->setText(QString());
        pushButton_enable2->setText(QString());
        label_ch2->setText(QCoreApplication::translate("WindowVm", "Channel 2", nullptr));
        groupBox_ch3->setTitle(QString());
        textBrowser_ch3->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.1240 V</span></p></body></html>", nullptr));
        doubleSpinBox_gain3->setPrefix(QString());
        label_5->setText(QCoreApplication::translate("WindowVm", "Gain:", nullptr));
        pushButton_disable3->setText(QString());
        pushButton_enable3->setText(QString());
        label_ch3->setText(QCoreApplication::translate("WindowVm", "Channel 3", nullptr));
        groupBox_ch4->setTitle(QString());
        textBrowser_ch4->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.1240 V</span></p></body></html>", nullptr));
        doubleSpinBox_gain4->setPrefix(QString());
        label_4->setText(QCoreApplication::translate("WindowVm", "Gain:", nullptr));
        pushButton_enable4->setText(QString());
        pushButton_disable4->setText(QString());
        label_ch4->setText(QCoreApplication::translate("WindowVm", "Channel 4", nullptr));
        groupBox_settigns->setTitle(QString());
        label_3->setText(QCoreApplication::translate("WindowVm", "Display Points:", nullptr));
        spinBox_display->setSuffix(QString());
        label_dial4->setText(QString());
        spinBox_average->setSuffix(QString());
        label_2->setText(QCoreApplication::translate("WindowVm", "Average:", nullptr));
        label_dial3->setText(QString());
        pushButton_disable->setText(QString());
        pushButton_enable->setText(QString());
        label_13->setText(QCoreApplication::translate("WindowVm", "Settings", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("WindowVm", "Help", nullptr));
        menuRecord->setTitle(QCoreApplication::translate("WindowVm", "Record", nullptr));
        menuFormat->setTitle(QCoreApplication::translate("WindowVm", "Format", nullptr));
        menuView->setTitle(QCoreApplication::translate("WindowVm", "View", nullptr));
        menuInterpolation->setTitle(QCoreApplication::translate("WindowVm", "Interpolation", nullptr));
        menuMeasure->setTitle(QCoreApplication::translate("WindowVm", "Measure", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowVm: public Ui_WindowVm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_VM_H
