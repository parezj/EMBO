/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionAbout;
    QAction *actionOpen;
    QWidget *centralwidget;
    QGroupBox *groupBox_ports;
    QListWidget *listWidget_ports;
    QPushButton *pushButton_Scan;
    QPushButton *pushButton_Connect;
    QPushButton *pushButton_Disconnect;
    QLabel *label_deviceLogo;
    QLabel *label_cvutlogo;
    QGroupBox *groupBox_device;
    QLabel *label_deviceName;
    QLabel *label_boardImg;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_dev_fw;
    QLabel *label_dev_fcpu;
    QLabel *label_dev_pins;
    QLabel *label_dev_lims;
    QLabel *label_dev_params;
    QGroupBox *groupBox_instr1;
    QGroupBox *groupBox_scope;
    QPushButton *pushButton_Scope;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_40;
    QGroupBox *groupBox_la;
    QPushButton *pushButton_la;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_14;
    QLabel *label_39;
    QGroupBox *groupBox_vm;
    QPushButton *pushButton_vm;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_18;
    QLabel *label_38;
    QGroupBox *groupBox_instr2;
    QGroupBox *groupBox_pwm;
    QPushButton *pushButton_pwm;
    QLabel *label_19;
    QLabel *label_20;
    QLabel *label_21;
    QLabel *label_22;
    QLabel *label_35;
    QGroupBox *groupBox_sgen;
    QPushButton *pushButton_sgen;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_29;
    QLabel *label_30;
    QLabel *label_36;
    QGroupBox *groupBox_cntr;
    QPushButton *pushButton_cntr;
    QLabel *label_37;
    QLabel *label_31;
    QLabel *label_32;
    QLabel *label_33;
    QLabel *label_34;
    QFrame *line;
    QMenuBar *menubar;
    QMenu *menuFile;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(800, 594);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(800, 594));
        MainWindow->setMaximumSize(QSize(800, 594));
        QIcon icon;
        icon.addFile(QString::fromUtf8("../logo/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        actionAbout = new QAction(MainWindow);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox_ports = new QGroupBox(centralwidget);
        groupBox_ports->setObjectName(QString::fromUtf8("groupBox_ports"));
        groupBox_ports->setGeometry(QRect(10, 0, 221, 541));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_ports->sizePolicy().hasHeightForWidth());
        groupBox_ports->setSizePolicy(sizePolicy1);
        QFont font;
        font.setPointSize(10);
        font.setBold(true);
        font.setWeight(75);
        groupBox_ports->setFont(font);
        listWidget_ports = new QListWidget(groupBox_ports);
        listWidget_ports->setObjectName(QString::fromUtf8("listWidget_ports"));
        listWidget_ports->setGeometry(QRect(10, 30, 201, 461));
        sizePolicy1.setHeightForWidth(listWidget_ports->sizePolicy().hasHeightForWidth());
        listWidget_ports->setSizePolicy(sizePolicy1);
        QFont font1;
        font1.setPointSize(12);
        font1.setBold(false);
        font1.setWeight(50);
        listWidget_ports->setFont(font1);
        listWidget_ports->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        listWidget_ports->setProperty("showDropIndicator", QVariant(false));
        listWidget_ports->setAlternatingRowColors(true);
        listWidget_ports->setSortingEnabled(false);
        pushButton_Scan = new QPushButton(groupBox_ports);
        pushButton_Scan->setObjectName(QString::fromUtf8("pushButton_Scan"));
        pushButton_Scan->setGeometry(QRect(10, 500, 81, 31));
        pushButton_Scan->setFont(font);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8("../../../../../fontawesome6/free/svgs/solid/magnifying-glass.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Scan->setIcon(icon1);
        pushButton_Connect = new QPushButton(groupBox_ports);
        pushButton_Connect->setObjectName(QString::fromUtf8("pushButton_Connect"));
        pushButton_Connect->setEnabled(false);
        pushButton_Connect->setGeometry(QRect(100, 500, 111, 31));
        pushButton_Connect->setFont(font);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8("../icons/power-off-green3.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Connect->setIcon(icon2);
        pushButton_Disconnect = new QPushButton(groupBox_ports);
        pushButton_Disconnect->setObjectName(QString::fromUtf8("pushButton_Disconnect"));
        pushButton_Disconnect->setEnabled(true);
        pushButton_Disconnect->setGeometry(QRect(100, 500, 111, 31));
        pushButton_Disconnect->setFont(font);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8("../icons/power-off-red.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Disconnect->setIcon(icon3);
        label_deviceLogo = new QLabel(groupBox_ports);
        label_deviceLogo->setObjectName(QString::fromUtf8("label_deviceLogo"));
        label_deviceLogo->setGeometry(QRect(150, 450, 31, 31));
        QFont font2;
        font2.setPointSize(14);
        font2.setBold(true);
        font2.setWeight(75);
        label_deviceLogo->setFont(font2);
        label_deviceLogo->setPixmap(QPixmap(QString::fromUtf8("../icon/icon2.png")));
        label_deviceLogo->setScaledContents(true);
        label_cvutlogo = new QLabel(groupBox_ports);
        label_cvutlogo->setObjectName(QString::fromUtf8("label_cvutlogo"));
        label_cvutlogo->setGeometry(QRect(20, 410, 161, 71));
        label_cvutlogo->setPixmap(QPixmap(QString::fromUtf8("../icons/logo_cvut_en_doplnkova_verze.svg")));
        label_cvutlogo->setScaledContents(true);
        groupBox_device = new QGroupBox(centralwidget);
        groupBox_device->setObjectName(QString::fromUtf8("groupBox_device"));
        groupBox_device->setGeometry(QRect(240, 0, 551, 181));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_device->sizePolicy().hasHeightForWidth());
        groupBox_device->setSizePolicy(sizePolicy2);
        groupBox_device->setFont(font);
        label_deviceName = new QLabel(groupBox_device);
        label_deviceName->setObjectName(QString::fromUtf8("label_deviceName"));
        label_deviceName->setGeometry(QRect(10, 20, 561, 21));
        label_deviceName->setFont(font2);
        label_boardImg = new QLabel(groupBox_device);
        label_boardImg->setObjectName(QString::fromUtf8("label_boardImg"));
        label_boardImg->setGeometry(QRect(240, 40, 291, 121));
        label_boardImg->setFont(font2);
        label_boardImg->setPixmap(QPixmap(QString::fromUtf8("D:/__CVUT/diplomka/bluepill.png")));
        label_boardImg->setScaledContents(true);
        label = new QLabel(groupBox_device);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 60, 81, 16));
        QFont font3;
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setWeight(50);
        label->setFont(font3);
        label->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(groupBox_device);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 80, 81, 16));
        label_2->setFont(font3);
        label_2->setTextFormat(Qt::AutoText);
        label_3 = new QLabel(groupBox_device);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 100, 81, 16));
        label_3->setFont(font3);
        label_3->setTextFormat(Qt::AutoText);
        label_4 = new QLabel(groupBox_device);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(20, 120, 81, 16));
        label_4->setFont(font3);
        label_4->setTextFormat(Qt::AutoText);
        label_5 = new QLabel(groupBox_device);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(20, 140, 81, 16));
        label_5->setFont(font3);
        label_5->setTextFormat(Qt::AutoText);
        label_dev_fw = new QLabel(groupBox_device);
        label_dev_fw->setObjectName(QString::fromUtf8("label_dev_fw"));
        label_dev_fw->setGeometry(QRect(110, 60, 121, 16));
        label_dev_fw->setFont(font3);
        label_dev_fw->setTextFormat(Qt::AutoText);
        label_dev_fcpu = new QLabel(groupBox_device);
        label_dev_fcpu->setObjectName(QString::fromUtf8("label_dev_fcpu"));
        label_dev_fcpu->setGeometry(QRect(110, 80, 121, 16));
        label_dev_fcpu->setFont(font3);
        label_dev_fcpu->setTextFormat(Qt::AutoText);
        label_dev_pins = new QLabel(groupBox_device);
        label_dev_pins->setObjectName(QString::fromUtf8("label_dev_pins"));
        label_dev_pins->setGeometry(QRect(110, 100, 121, 16));
        label_dev_pins->setFont(font3);
        label_dev_pins->setTextFormat(Qt::AutoText);
        label_dev_lims = new QLabel(groupBox_device);
        label_dev_lims->setObjectName(QString::fromUtf8("label_dev_lims"));
        label_dev_lims->setGeometry(QRect(110, 120, 121, 16));
        label_dev_lims->setFont(font3);
        label_dev_lims->setTextFormat(Qt::AutoText);
        label_dev_params = new QLabel(groupBox_device);
        label_dev_params->setObjectName(QString::fromUtf8("label_dev_params"));
        label_dev_params->setGeometry(QRect(110, 140, 121, 16));
        label_dev_params->setFont(font3);
        label_dev_params->setTextFormat(Qt::AutoText);
        groupBox_instr1 = new QGroupBox(centralwidget);
        groupBox_instr1->setObjectName(QString::fromUtf8("groupBox_instr1"));
        groupBox_instr1->setGeometry(QRect(240, 180, 551, 181));
        sizePolicy2.setHeightForWidth(groupBox_instr1->sizePolicy().hasHeightForWidth());
        groupBox_instr1->setSizePolicy(sizePolicy2);
        groupBox_instr1->setFont(font);
        groupBox_scope = new QGroupBox(groupBox_instr1);
        groupBox_scope->setObjectName(QString::fromUtf8("groupBox_scope"));
        groupBox_scope->setGeometry(QRect(10, 20, 171, 151));
        groupBox_scope->setFont(font3);
        pushButton_Scope = new QPushButton(groupBox_scope);
        pushButton_Scope->setObjectName(QString::fromUtf8("pushButton_Scope"));
        pushButton_Scope->setGeometry(QRect(0, 110, 171, 41));
        QFont font4;
        font4.setPointSize(12);
        font4.setBold(true);
        font4.setWeight(75);
        pushButton_Scope->setFont(font4);
        pushButton_Scope->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 2px solid rgb(100, 100, 100);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 2px solid black;\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8("../icons/waveform2.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_Scope->setIcon(icon4);
        pushButton_Scope->setIconSize(QSize(22, 22));
        label_6 = new QLabel(groupBox_scope);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 10, 111, 16));
        QFont font5;
        font5.setPointSize(9);
        font5.setBold(false);
        font5.setWeight(50);
        label_6->setFont(font5);
        label_6->setTextFormat(Qt::AutoText);
        label_8 = new QLabel(groupBox_scope);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 30, 111, 16));
        label_8->setFont(font5);
        label_8->setTextFormat(Qt::AutoText);
        label_9 = new QLabel(groupBox_scope);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 50, 111, 16));
        label_9->setFont(font5);
        label_9->setTextFormat(Qt::AutoText);
        label_10 = new QLabel(groupBox_scope);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 70, 111, 16));
        label_10->setFont(font5);
        label_10->setTextFormat(Qt::AutoText);
        label_40 = new QLabel(groupBox_scope);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setGeometry(QRect(10, 90, 111, 16));
        QFont font6;
        font6.setPointSize(9);
        label_40->setFont(font6);
        label_40->setTextFormat(Qt::AutoText);
        groupBox_la = new QGroupBox(groupBox_instr1);
        groupBox_la->setObjectName(QString::fromUtf8("groupBox_la"));
        groupBox_la->setGeometry(QRect(190, 20, 171, 151));
        groupBox_la->setFont(font3);
        pushButton_la = new QPushButton(groupBox_la);
        pushButton_la->setObjectName(QString::fromUtf8("pushButton_la"));
        pushButton_la->setGeometry(QRect(0, 110, 171, 41));
        pushButton_la->setFont(font4);
        pushButton_la->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 2px solid rgb(100, 100, 100);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 2px solid black;\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8("../icons/wave-square.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_la->setIcon(icon5);
        pushButton_la->setIconSize(QSize(22, 22));
        label_11 = new QLabel(groupBox_la);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 10, 111, 16));
        label_11->setFont(font5);
        label_11->setTextFormat(Qt::AutoText);
        label_12 = new QLabel(groupBox_la);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 30, 111, 16));
        label_12->setFont(font5);
        label_12->setTextFormat(Qt::AutoText);
        label_13 = new QLabel(groupBox_la);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 50, 111, 16));
        label_13->setFont(font5);
        label_13->setTextFormat(Qt::AutoText);
        label_14 = new QLabel(groupBox_la);
        label_14->setObjectName(QString::fromUtf8("label_14"));
        label_14->setGeometry(QRect(10, 70, 111, 16));
        label_14->setFont(font5);
        label_14->setTextFormat(Qt::AutoText);
        label_39 = new QLabel(groupBox_la);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(10, 90, 111, 16));
        label_39->setFont(font6);
        label_39->setTextFormat(Qt::AutoText);
        groupBox_vm = new QGroupBox(groupBox_instr1);
        groupBox_vm->setObjectName(QString::fromUtf8("groupBox_vm"));
        groupBox_vm->setGeometry(QRect(370, 20, 171, 151));
        groupBox_vm->setFont(font3);
        pushButton_vm = new QPushButton(groupBox_vm);
        pushButton_vm->setObjectName(QString::fromUtf8("pushButton_vm"));
        pushButton_vm->setGeometry(QRect(0, 110, 171, 41));
        pushButton_vm->setFont(font4);
        pushButton_vm->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 2px solid rgb(100, 100, 100);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 2px solid black;\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"}"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8("../icons/gauge.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_vm->setIcon(icon6);
        pushButton_vm->setIconSize(QSize(22, 22));
        label_15 = new QLabel(groupBox_vm);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 10, 111, 16));
        label_15->setFont(font5);
        label_15->setTextFormat(Qt::AutoText);
        label_16 = new QLabel(groupBox_vm);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 30, 111, 16));
        label_16->setFont(font5);
        label_16->setTextFormat(Qt::AutoText);
        label_17 = new QLabel(groupBox_vm);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 50, 111, 16));
        label_17->setFont(font5);
        label_17->setTextFormat(Qt::AutoText);
        label_18 = new QLabel(groupBox_vm);
        label_18->setObjectName(QString::fromUtf8("label_18"));
        label_18->setGeometry(QRect(10, 70, 111, 16));
        label_18->setFont(font5);
        label_18->setTextFormat(Qt::AutoText);
        label_38 = new QLabel(groupBox_vm);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(10, 90, 111, 16));
        label_38->setFont(font6);
        label_38->setTextFormat(Qt::AutoText);
        groupBox_instr2 = new QGroupBox(centralwidget);
        groupBox_instr2->setObjectName(QString::fromUtf8("groupBox_instr2"));
        groupBox_instr2->setGeometry(QRect(240, 360, 551, 181));
        sizePolicy2.setHeightForWidth(groupBox_instr2->sizePolicy().hasHeightForWidth());
        groupBox_instr2->setSizePolicy(sizePolicy2);
        groupBox_instr2->setFont(font);
        groupBox_pwm = new QGroupBox(groupBox_instr2);
        groupBox_pwm->setObjectName(QString::fromUtf8("groupBox_pwm"));
        groupBox_pwm->setGeometry(QRect(10, 20, 171, 151));
        groupBox_pwm->setFont(font3);
        pushButton_pwm = new QPushButton(groupBox_pwm);
        pushButton_pwm->setObjectName(QString::fromUtf8("pushButton_pwm"));
        pushButton_pwm->setGeometry(QRect(0, 110, 171, 41));
        pushButton_pwm->setFont(font4);
        pushButton_pwm->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 2px solid rgb(100, 100, 100);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 2px solid black;\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"}"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8("../icons/square-poll-vertical.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_pwm->setIcon(icon7);
        pushButton_pwm->setIconSize(QSize(22, 22));
        label_19 = new QLabel(groupBox_pwm);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(10, 10, 111, 16));
        label_19->setFont(font5);
        label_19->setTextFormat(Qt::AutoText);
        label_20 = new QLabel(groupBox_pwm);
        label_20->setObjectName(QString::fromUtf8("label_20"));
        label_20->setGeometry(QRect(10, 30, 111, 16));
        label_20->setFont(font5);
        label_20->setTextFormat(Qt::AutoText);
        label_21 = new QLabel(groupBox_pwm);
        label_21->setObjectName(QString::fromUtf8("label_21"));
        label_21->setGeometry(QRect(10, 50, 111, 16));
        label_21->setFont(font5);
        label_21->setTextFormat(Qt::AutoText);
        label_22 = new QLabel(groupBox_pwm);
        label_22->setObjectName(QString::fromUtf8("label_22"));
        label_22->setGeometry(QRect(10, 70, 111, 16));
        label_22->setFont(font5);
        label_22->setTextFormat(Qt::AutoText);
        label_35 = new QLabel(groupBox_pwm);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(10, 90, 111, 16));
        label_35->setFont(font6);
        label_35->setTextFormat(Qt::AutoText);
        groupBox_sgen = new QGroupBox(groupBox_instr2);
        groupBox_sgen->setObjectName(QString::fromUtf8("groupBox_sgen"));
        groupBox_sgen->setGeometry(QRect(190, 20, 171, 151));
        groupBox_sgen->setFont(font3);
        pushButton_sgen = new QPushButton(groupBox_sgen);
        pushButton_sgen->setObjectName(QString::fromUtf8("pushButton_sgen"));
        pushButton_sgen->setGeometry(QRect(0, 110, 171, 41));
        pushButton_sgen->setFont(font4);
        pushButton_sgen->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 2px solid rgb(100, 100, 100);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 2px solid black;\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"}"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8("../icons/wave-sine.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_sgen->setIcon(icon8);
        pushButton_sgen->setIconSize(QSize(22, 22));
        label_27 = new QLabel(groupBox_sgen);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(10, 10, 111, 16));
        label_27->setFont(font5);
        label_27->setTextFormat(Qt::AutoText);
        label_28 = new QLabel(groupBox_sgen);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(10, 30, 111, 16));
        label_28->setFont(font5);
        label_28->setTextFormat(Qt::AutoText);
        label_29 = new QLabel(groupBox_sgen);
        label_29->setObjectName(QString::fromUtf8("label_29"));
        label_29->setGeometry(QRect(10, 50, 111, 16));
        label_29->setFont(font5);
        label_29->setTextFormat(Qt::AutoText);
        label_30 = new QLabel(groupBox_sgen);
        label_30->setObjectName(QString::fromUtf8("label_30"));
        label_30->setGeometry(QRect(10, 70, 111, 16));
        label_30->setFont(font5);
        label_30->setTextFormat(Qt::AutoText);
        label_36 = new QLabel(groupBox_sgen);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(10, 90, 111, 16));
        label_36->setFont(font6);
        label_36->setTextFormat(Qt::AutoText);
        groupBox_cntr = new QGroupBox(groupBox_instr2);
        groupBox_cntr->setObjectName(QString::fromUtf8("groupBox_cntr"));
        groupBox_cntr->setGeometry(QRect(370, 20, 171, 151));
        groupBox_cntr->setFont(font3);
        pushButton_cntr = new QPushButton(groupBox_cntr);
        pushButton_cntr->setObjectName(QString::fromUtf8("pushButton_cntr"));
        pushButton_cntr->setGeometry(QRect(0, 110, 171, 41));
        pushButton_cntr->setFont(font4);
        pushButton_cntr->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 2px solid rgb(100, 100, 100);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 2px solid black;\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"}"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8("../icons/stopwatch-20.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_cntr->setIcon(icon9);
        pushButton_cntr->setIconSize(QSize(22, 22));
        label_37 = new QLabel(groupBox_cntr);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(10, 90, 111, 16));
        label_37->setFont(font6);
        label_37->setTextFormat(Qt::AutoText);
        label_31 = new QLabel(groupBox_cntr);
        label_31->setObjectName(QString::fromUtf8("label_31"));
        label_31->setGeometry(QRect(10, 50, 111, 16));
        label_31->setFont(font6);
        label_31->setTextFormat(Qt::AutoText);
        label_32 = new QLabel(groupBox_cntr);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(10, 10, 111, 16));
        label_32->setFont(font6);
        label_32->setTextFormat(Qt::AutoText);
        label_33 = new QLabel(groupBox_cntr);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(10, 70, 111, 16));
        label_33->setFont(font6);
        label_33->setTextFormat(Qt::AutoText);
        label_34 = new QLabel(groupBox_cntr);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(10, 30, 111, 16));
        label_34->setFont(font6);
        label_34->setTextFormat(Qt::AutoText);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 540, 801, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menubar->setFont(font6);
        menuFile = new QMenu(menubar);
        menuFile->setObjectName(QString::fromUtf8("menuFile"));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QFont font7;
        font7.setPointSize(8);
        statusbar->setFont(font7);
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuFile->menuAction());
        menubar->addAction(menuAbout->menuAction());
        menuFile->addAction(actionOpen);
        menuAbout->addAction(actionAbout);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "EMBO - EMBedded Oscilloscope", nullptr));
        actionAbout->setText(QCoreApplication::translate("MainWindow", "About", nullptr));
#if QT_CONFIG(shortcut)
        actionAbout->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("MainWindow", "Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("MainWindow", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBox_ports->setTitle(QCoreApplication::translate("MainWindow", "Devices", nullptr));
#if QT_CONFIG(accessibility)
        listWidget_ports->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        pushButton_Scan->setText(QCoreApplication::translate("MainWindow", "Scan", nullptr));
        pushButton_Connect->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        pushButton_Disconnect->setText(QCoreApplication::translate("MainWindow", "Disconnect", nullptr));
        label_deviceLogo->setText(QString());
        label_cvutlogo->setText(QString());
        groupBox_device->setTitle(QString());
        label_deviceName->setText(QCoreApplication::translate("MainWindow", "EMBO-STM32F103-UART", nullptr));
        label_boardImg->setText(QString());
        label->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Firmware:", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "\342\200\242 FCPU:", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Pins:", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Limits:", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Params:", nullptr));
        label_dev_fw->setText(QCoreApplication::translate("MainWindow", "?", nullptr));
        label_dev_fcpu->setText(QCoreApplication::translate("MainWindow", "?", nullptr));
        label_dev_pins->setText(QCoreApplication::translate("MainWindow", "?", nullptr));
        label_dev_lims->setText(QCoreApplication::translate("MainWindow", "?", nullptr));
        label_dev_params->setText(QCoreApplication::translate("MainWindow", "?", nullptr));
        groupBox_instr1->setTitle(QCoreApplication::translate("MainWindow", "Main Instruments", nullptr));
        groupBox_scope->setTitle(QString());
        pushButton_Scope->setText(QCoreApplication::translate("MainWindow", "Oscilloscope", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max fs:", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max mem:", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Channs:", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Features:", nullptr));
        label_40->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Pins:", nullptr));
        groupBox_la->setTitle(QString());
        pushButton_la->setText(QCoreApplication::translate("MainWindow", "Logic Analyzer", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max fs:", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max mem:", nullptr));
        label_13->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Channs:", nullptr));
        label_14->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Features:", nullptr));
        label_39->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Pins:", nullptr));
        groupBox_vm->setTitle(QString());
        pushButton_vm->setText(QCoreApplication::translate("MainWindow", "Voltmeter", nullptr));
        label_15->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max fs:", nullptr));
        label_16->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max mem:", nullptr));
        label_17->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Channs:", nullptr));
        label_18->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Features:", nullptr));
        label_38->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Pins:", nullptr));
        groupBox_instr2->setTitle(QCoreApplication::translate("MainWindow", "Aux Instruments", nullptr));
        groupBox_pwm->setTitle(QString());
        pushButton_pwm->setText(QCoreApplication::translate("MainWindow", "PWM Generator", nullptr));
        label_19->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max fs:", nullptr));
        label_20->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max mem:", nullptr));
        label_21->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Channs:", nullptr));
        label_22->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Features:", nullptr));
        label_35->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Pins:", nullptr));
        groupBox_sgen->setTitle(QString());
        pushButton_sgen->setText(QCoreApplication::translate("MainWindow", "Signal Generator", nullptr));
        label_27->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max fs:", nullptr));
        label_28->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max mem:", nullptr));
        label_29->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Channs:", nullptr));
        label_30->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Features:", nullptr));
        label_36->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Pins:", nullptr));
        groupBox_cntr->setTitle(QString());
        pushButton_cntr->setText(QCoreApplication::translate("MainWindow", "Counter", nullptr));
        label_37->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Pins:", nullptr));
        label_31->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Channs:", nullptr));
        label_32->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max fs:", nullptr));
        label_33->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Features:", nullptr));
        label_34->setText(QCoreApplication::translate("MainWindow", "\342\200\242 Max mem:", nullptr));
        menuFile->setTitle(QCoreApplication::translate("MainWindow", "File", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("MainWindow", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
