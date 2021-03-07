/********************************************************************************
** Form generated from reading UI file 'window__main.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW__MAIN_H
#define UI_WINDOW__MAIN_H

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

class Ui_WindowMain
{
public:
    QAction *actionAbout;
    QAction *actionOpen;
    QWidget *centralwidget;
    QGroupBox *groupBox_ports;
    QListWidget *listWidget_ports;
    QPushButton *pushButton_scan;
    QPushButton *pushButton_connect;
    QPushButton *pushButton_disconnect;
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
    QLabel *label_dev_comm;
    QLabel *label_dev_rtos;
    QLabel *label_dev_ll;
    QLabel *label_7;
    QLabel *label_dev_vref;
    QGroupBox *groupBox_instr1;
    QGroupBox *groupBox_scope;
    QPushButton *pushButton_scope;
    QLabel *label_6;
    QLabel *label_8;
    QLabel *label_9;
    QLabel *label_10;
    QLabel *label_40;
    QLabel *label_scope_fs;
    QLabel *label_scope_mem;
    QLabel *label_scope_bits;
    QLabel *label_scope_modes;
    QLabel *label_scope_pins;
    QGroupBox *groupBox_la;
    QPushButton *pushButton_la;
    QLabel *label_11;
    QLabel *label_12;
    QLabel *label_13;
    QLabel *label_39;
    QLabel *label_la_pins;
    QLabel *label_la_protocols;
    QLabel *label_la_fs;
    QLabel *label_la_mem;
    QGroupBox *groupBox_vm;
    QPushButton *pushButton_vm;
    QLabel *label_15;
    QLabel *label_16;
    QLabel *label_17;
    QLabel *label_38;
    QLabel *label_vm_fs;
    QLabel *label_vm_mem;
    QLabel *label_vm_bits;
    QLabel *label_vm_pins;
    QGroupBox *groupBox_instr2;
    QGroupBox *groupBox_pwm;
    QPushButton *pushButton_pwm;
    QLabel *label_19;
    QLabel *label_35;
    QLabel *label_pwm_pins;
    QLabel *label_pwm_freq;
    QLabel *label_pwm_mode;
    QLabel *label_33;
    QGroupBox *groupBox_sgen;
    QPushButton *pushButton_sgen;
    QLabel *label_27;
    QLabel *label_28;
    QLabel *label_36;
    QLabel *label_sgen_pins;
    QLabel *label_sgen_mem;
    QLabel *label_sgen_freq;
    QGroupBox *groupBox_cntr;
    QPushButton *pushButton_cntr;
    QLabel *label_37;
    QLabel *label_32;
    QLabel *label_34;
    QLabel *label_cntr_mode;
    QLabel *label_cntr_pins;
    QLabel *label_cntr_timeout;
    QFrame *line;
    QMenuBar *menubar;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowMain)
    {
        if (WindowMain->objectName().isEmpty())
            WindowMain->setObjectName(QString::fromUtf8("WindowMain"));
        WindowMain->resize(800, 594);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WindowMain->sizePolicy().hasHeightForWidth());
        WindowMain->setSizePolicy(sizePolicy);
        WindowMain->setMinimumSize(QSize(800, 594));
        WindowMain->setMaximumSize(QSize(800, 594));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setItalic(false);
        font.setKerning(true);
        WindowMain->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowMain->setWindowIcon(icon);
        actionAbout = new QAction(WindowMain);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        actionAbout->setCheckable(false);
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(10);
        font1.setItalic(false);
        actionAbout->setFont(font1);
        actionOpen = new QAction(WindowMain);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        centralwidget = new QWidget(WindowMain);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        groupBox_ports = new QGroupBox(centralwidget);
        groupBox_ports->setObjectName(QString::fromUtf8("groupBox_ports"));
        groupBox_ports->setGeometry(QRect(10, 0, 221, 541));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_ports->sizePolicy().hasHeightForWidth());
        groupBox_ports->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto Medium"));
        font2.setPointSize(11);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        font2.setKerning(true);
        groupBox_ports->setFont(font2);
        groupBox_ports->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        listWidget_ports = new QListWidget(groupBox_ports);
        new QListWidgetItem(listWidget_ports);
        new QListWidgetItem(listWidget_ports);
        listWidget_ports->setObjectName(QString::fromUtf8("listWidget_ports"));
        listWidget_ports->setGeometry(QRect(10, 30, 201, 451));
        sizePolicy1.setHeightForWidth(listWidget_ports->sizePolicy().hasHeightForWidth());
        listWidget_ports->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Roboto"));
        font3.setPointSize(13);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        font3.setKerning(true);
        listWidget_ports->setFont(font3);
        listWidget_ports->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
        listWidget_ports->setProperty("showDropIndicator", QVariant(false));
        listWidget_ports->setAlternatingRowColors(true);
        listWidget_ports->setSortingEnabled(false);
        pushButton_scan = new QPushButton(groupBox_ports);
        pushButton_scan->setObjectName(QString::fromUtf8("pushButton_scan"));
        pushButton_scan->setGeometry(QRect(10, 490, 71, 41));
        pushButton_scan->setFont(font3);
        pushButton_scan->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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
        icon2.addFile(QString::fromUtf8(":/main/resources/img/magnifying-glass.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_scan->setIcon(icon2);
        pushButton_connect = new QPushButton(groupBox_ports);
        pushButton_connect->setObjectName(QString::fromUtf8("pushButton_connect"));
        pushButton_connect->setEnabled(false);
        pushButton_connect->setGeometry(QRect(90, 490, 121, 41));
        pushButton_connect->setFont(font3);
        pushButton_connect->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(100, 100, 100);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid black;\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 1px solid black;\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_connect->setIcon(icon3);
        pushButton_disconnect = new QPushButton(groupBox_ports);
        pushButton_disconnect->setObjectName(QString::fromUtf8("pushButton_disconnect"));
        pushButton_disconnect->setEnabled(true);
        pushButton_disconnect->setGeometry(QRect(90, 490, 121, 41));
        pushButton_disconnect->setFont(font3);
        pushButton_disconnect->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/main/resources/img/power-off-red.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_disconnect->setIcon(icon4);
        label_cvutlogo = new QLabel(groupBox_ports);
        label_cvutlogo->setObjectName(QString::fromUtf8("label_cvutlogo"));
        label_cvutlogo->setGeometry(QRect(20, 360, 161, 110));
        label_cvutlogo->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/ctu_meas_small.png")));
        label_cvutlogo->setScaledContents(true);
        groupBox_device = new QGroupBox(centralwidget);
        groupBox_device->setObjectName(QString::fromUtf8("groupBox_device"));
        groupBox_device->setGeometry(QRect(240, 0, 551, 181));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(groupBox_device->sizePolicy().hasHeightForWidth());
        groupBox_device->setSizePolicy(sizePolicy2);
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto"));
        font4.setPointSize(10);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        font4.setKerning(true);
        groupBox_device->setFont(font4);
        groupBox_device->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        label_deviceName = new QLabel(groupBox_device);
        label_deviceName->setObjectName(QString::fromUtf8("label_deviceName"));
        label_deviceName->setGeometry(QRect(10, 20, 361, 21));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Roboto Black"));
        font5.setPointSize(14);
        font5.setBold(true);
        font5.setItalic(false);
        font5.setWeight(75);
        font5.setKerning(true);
        label_deviceName->setFont(font5);
        label_boardImg = new QLabel(groupBox_device);
        label_boardImg->setObjectName(QString::fromUtf8("label_boardImg"));
        label_boardImg->setGeometry(QRect(360, 20, 181, 151));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Roboto"));
        font6.setPointSize(14);
        font6.setBold(true);
        font6.setItalic(false);
        font6.setWeight(75);
        font6.setKerning(true);
        label_boardImg->setFont(font6);
        label_boardImg->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/unknown2.png")));
        label_boardImg->setScaledContents(true);
        label = new QLabel(groupBox_device);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 50, 141, 16));
        label->setFont(font4);
        label->setTextFormat(Qt::AutoText);
        label_2 = new QLabel(groupBox_device);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(10, 70, 141, 16));
        label_2->setFont(font4);
        label_2->setTextFormat(Qt::AutoText);
        label_3 = new QLabel(groupBox_device);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 90, 141, 16));
        label_3->setFont(font4);
        label_3->setTextFormat(Qt::AutoText);
        label_4 = new QLabel(groupBox_device);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 110, 141, 16));
        label_4->setFont(font4);
        label_4->setTextFormat(Qt::AutoText);
        label_5 = new QLabel(groupBox_device);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(10, 130, 141, 16));
        label_5->setFont(font4);
        label_5->setTextFormat(Qt::AutoText);
        label_dev_fw = new QLabel(groupBox_device);
        label_dev_fw->setObjectName(QString::fromUtf8("label_dev_fw"));
        label_dev_fw->setGeometry(QRect(160, 50, 191, 20));
        label_dev_fw->setFont(font4);
        label_dev_fw->setTextFormat(Qt::AutoText);
        label_dev_fcpu = new QLabel(groupBox_device);
        label_dev_fcpu->setObjectName(QString::fromUtf8("label_dev_fcpu"));
        label_dev_fcpu->setGeometry(QRect(160, 110, 191, 20));
        label_dev_fcpu->setFont(font4);
        label_dev_fcpu->setTextFormat(Qt::AutoText);
        label_dev_comm = new QLabel(groupBox_device);
        label_dev_comm->setObjectName(QString::fromUtf8("label_dev_comm"));
        label_dev_comm->setGeometry(QRect(160, 130, 191, 20));
        label_dev_comm->setFont(font4);
        label_dev_comm->setTextFormat(Qt::AutoText);
        label_dev_rtos = new QLabel(groupBox_device);
        label_dev_rtos->setObjectName(QString::fromUtf8("label_dev_rtos"));
        label_dev_rtos->setGeometry(QRect(160, 90, 191, 20));
        label_dev_rtos->setFont(font4);
        label_dev_rtos->setTextFormat(Qt::AutoText);
        label_dev_ll = new QLabel(groupBox_device);
        label_dev_ll->setObjectName(QString::fromUtf8("label_dev_ll"));
        label_dev_ll->setGeometry(QRect(160, 70, 191, 20));
        label_dev_ll->setFont(font4);
        label_dev_ll->setTextFormat(Qt::AutoText);
        label_7 = new QLabel(groupBox_device);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(10, 150, 141, 16));
        label_7->setFont(font4);
        label_7->setTextFormat(Qt::AutoText);
        label_dev_vref = new QLabel(groupBox_device);
        label_dev_vref->setObjectName(QString::fromUtf8("label_dev_vref"));
        label_dev_vref->setGeometry(QRect(160, 150, 191, 20));
        label_dev_vref->setFont(font4);
        label_dev_vref->setTextFormat(Qt::AutoText);
        label_boardImg->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_4->raise();
        label_5->raise();
        label_dev_fw->raise();
        label_dev_fcpu->raise();
        label_dev_comm->raise();
        label_dev_rtos->raise();
        label_dev_ll->raise();
        label_7->raise();
        label_dev_vref->raise();
        label_deviceName->raise();
        groupBox_instr1 = new QGroupBox(centralwidget);
        groupBox_instr1->setObjectName(QString::fromUtf8("groupBox_instr1"));
        groupBox_instr1->setGeometry(QRect(240, 180, 551, 181));
        sizePolicy2.setHeightForWidth(groupBox_instr1->sizePolicy().hasHeightForWidth());
        groupBox_instr1->setSizePolicy(sizePolicy2);
        groupBox_instr1->setFont(font2);
        groupBox_instr1->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        groupBox_scope = new QGroupBox(groupBox_instr1);
        groupBox_scope->setObjectName(QString::fromUtf8("groupBox_scope"));
        groupBox_scope->setGeometry(QRect(10, 20, 171, 151));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Roboto"));
        font7.setPointSize(11);
        font7.setBold(false);
        font7.setItalic(false);
        font7.setWeight(50);
        font7.setKerning(true);
        groupBox_scope->setFont(font7);
        groupBox_scope->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(190,220,240, 0.5);border: 1px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        pushButton_scope = new QPushButton(groupBox_scope);
        pushButton_scope->setObjectName(QString::fromUtf8("pushButton_scope"));
        pushButton_scope->setGeometry(QRect(0, 110, 171, 41));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Roboto"));
        font8.setPointSize(13);
        font8.setBold(false);
        font8.setWeight(50);
        font8.setKerning(false);
        pushButton_scope->setFont(font8);
        pushButton_scope->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/main/resources/img/scope.svg"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_scope->setIcon(icon5);
        pushButton_scope->setIconSize(QSize(21, 21));
        label_6 = new QLabel(groupBox_scope);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(10, 10, 61, 16));
        label_6->setFont(font4);
        label_6->setTextFormat(Qt::AutoText);
        label_8 = new QLabel(groupBox_scope);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(10, 30, 61, 16));
        label_8->setFont(font4);
        label_8->setTextFormat(Qt::AutoText);
        label_9 = new QLabel(groupBox_scope);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(10, 50, 61, 16));
        label_9->setFont(font4);
        label_9->setTextFormat(Qt::AutoText);
        label_10 = new QLabel(groupBox_scope);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(10, 70, 61, 16));
        label_10->setFont(font4);
        label_10->setTextFormat(Qt::AutoText);
        label_40 = new QLabel(groupBox_scope);
        label_40->setObjectName(QString::fromUtf8("label_40"));
        label_40->setGeometry(QRect(10, 90, 61, 16));
        label_40->setFont(font4);
        label_40->setTextFormat(Qt::AutoText);
        label_scope_fs = new QLabel(groupBox_scope);
        label_scope_fs->setObjectName(QString::fromUtf8("label_scope_fs"));
        label_scope_fs->setGeometry(QRect(70, 10, 101, 16));
        label_scope_fs->setFont(font4);
        label_scope_fs->setTextFormat(Qt::AutoText);
        label_scope_mem = new QLabel(groupBox_scope);
        label_scope_mem->setObjectName(QString::fromUtf8("label_scope_mem"));
        label_scope_mem->setGeometry(QRect(70, 30, 101, 16));
        label_scope_mem->setFont(font4);
        label_scope_mem->setTextFormat(Qt::AutoText);
        label_scope_bits = new QLabel(groupBox_scope);
        label_scope_bits->setObjectName(QString::fromUtf8("label_scope_bits"));
        label_scope_bits->setGeometry(QRect(70, 50, 101, 16));
        label_scope_bits->setFont(font4);
        label_scope_bits->setTextFormat(Qt::AutoText);
        label_scope_modes = new QLabel(groupBox_scope);
        label_scope_modes->setObjectName(QString::fromUtf8("label_scope_modes"));
        label_scope_modes->setGeometry(QRect(70, 70, 101, 16));
        label_scope_modes->setFont(font4);
        label_scope_modes->setTextFormat(Qt::AutoText);
        label_scope_pins = new QLabel(groupBox_scope);
        label_scope_pins->setObjectName(QString::fromUtf8("label_scope_pins"));
        label_scope_pins->setGeometry(QRect(70, 90, 101, 16));
        label_scope_pins->setFont(font4);
        label_scope_pins->setTextFormat(Qt::AutoText);
        groupBox_la = new QGroupBox(groupBox_instr1);
        groupBox_la->setObjectName(QString::fromUtf8("groupBox_la"));
        groupBox_la->setGeometry(QRect(190, 20, 171, 151));
        groupBox_la->setFont(font7);
        groupBox_la->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(240,190,190, 0.5);border: 1px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        pushButton_la = new QPushButton(groupBox_la);
        pushButton_la->setObjectName(QString::fromUtf8("pushButton_la"));
        pushButton_la->setGeometry(QRect(0, 110, 171, 41));
        pushButton_la->setFont(font8);
        pushButton_la->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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
"	border: 2px solid rgb(150, 150, 150);;\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/main/resources/img/la.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_la->setIcon(icon6);
        pushButton_la->setIconSize(QSize(21, 21));
        label_11 = new QLabel(groupBox_la);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(10, 10, 61, 16));
        label_11->setFont(font4);
        label_11->setTextFormat(Qt::AutoText);
        label_12 = new QLabel(groupBox_la);
        label_12->setObjectName(QString::fromUtf8("label_12"));
        label_12->setGeometry(QRect(10, 30, 61, 16));
        label_12->setFont(font4);
        label_12->setTextFormat(Qt::AutoText);
        label_13 = new QLabel(groupBox_la);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setGeometry(QRect(10, 50, 71, 16));
        label_13->setFont(font4);
        label_13->setTextFormat(Qt::AutoText);
        label_39 = new QLabel(groupBox_la);
        label_39->setObjectName(QString::fromUtf8("label_39"));
        label_39->setGeometry(QRect(10, 70, 61, 16));
        label_39->setFont(font4);
        label_39->setTextFormat(Qt::AutoText);
        label_la_pins = new QLabel(groupBox_la);
        label_la_pins->setObjectName(QString::fromUtf8("label_la_pins"));
        label_la_pins->setGeometry(QRect(70, 70, 101, 20));
        label_la_pins->setFont(font4);
        label_la_pins->setTextFormat(Qt::AutoText);
        label_la_protocols = new QLabel(groupBox_la);
        label_la_protocols->setObjectName(QString::fromUtf8("label_la_protocols"));
        label_la_protocols->setGeometry(QRect(70, 50, 101, 16));
        label_la_protocols->setFont(font4);
        label_la_protocols->setTextFormat(Qt::AutoText);
        label_la_fs = new QLabel(groupBox_la);
        label_la_fs->setObjectName(QString::fromUtf8("label_la_fs"));
        label_la_fs->setGeometry(QRect(70, 10, 101, 16));
        label_la_fs->setFont(font4);
        label_la_fs->setTextFormat(Qt::AutoText);
        label_la_mem = new QLabel(groupBox_la);
        label_la_mem->setObjectName(QString::fromUtf8("label_la_mem"));
        label_la_mem->setGeometry(QRect(70, 30, 101, 16));
        label_la_mem->setFont(font4);
        label_la_mem->setTextFormat(Qt::AutoText);
        groupBox_vm = new QGroupBox(groupBox_instr1);
        groupBox_vm->setObjectName(QString::fromUtf8("groupBox_vm"));
        groupBox_vm->setGeometry(QRect(370, 20, 171, 151));
        groupBox_vm->setFont(font7);
        groupBox_vm->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(240,230,190, 0.5);border: 1px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        pushButton_vm = new QPushButton(groupBox_vm);
        pushButton_vm->setObjectName(QString::fromUtf8("pushButton_vm"));
        pushButton_vm->setGeometry(QRect(0, 110, 171, 41));
        pushButton_vm->setFont(font8);
        pushButton_vm->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/main/resources/img/vm.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_vm->setIcon(icon7);
        pushButton_vm->setIconSize(QSize(22, 22));
        label_15 = new QLabel(groupBox_vm);
        label_15->setObjectName(QString::fromUtf8("label_15"));
        label_15->setGeometry(QRect(10, 10, 51, 16));
        label_15->setFont(font4);
        label_15->setTextFormat(Qt::AutoText);
        label_16 = new QLabel(groupBox_vm);
        label_16->setObjectName(QString::fromUtf8("label_16"));
        label_16->setGeometry(QRect(10, 30, 51, 16));
        label_16->setFont(font4);
        label_16->setTextFormat(Qt::AutoText);
        label_17 = new QLabel(groupBox_vm);
        label_17->setObjectName(QString::fromUtf8("label_17"));
        label_17->setGeometry(QRect(10, 50, 51, 16));
        label_17->setFont(font4);
        label_17->setTextFormat(Qt::AutoText);
        label_38 = new QLabel(groupBox_vm);
        label_38->setObjectName(QString::fromUtf8("label_38"));
        label_38->setGeometry(QRect(10, 70, 51, 16));
        label_38->setFont(font4);
        label_38->setTextFormat(Qt::AutoText);
        label_vm_fs = new QLabel(groupBox_vm);
        label_vm_fs->setObjectName(QString::fromUtf8("label_vm_fs"));
        label_vm_fs->setGeometry(QRect(70, 10, 91, 20));
        label_vm_fs->setFont(font4);
        label_vm_fs->setTextFormat(Qt::AutoText);
        label_vm_mem = new QLabel(groupBox_vm);
        label_vm_mem->setObjectName(QString::fromUtf8("label_vm_mem"));
        label_vm_mem->setGeometry(QRect(70, 30, 91, 20));
        label_vm_mem->setFont(font4);
        label_vm_mem->setTextFormat(Qt::AutoText);
        label_vm_bits = new QLabel(groupBox_vm);
        label_vm_bits->setObjectName(QString::fromUtf8("label_vm_bits"));
        label_vm_bits->setGeometry(QRect(70, 50, 91, 20));
        label_vm_bits->setFont(font4);
        label_vm_bits->setTextFormat(Qt::AutoText);
        label_vm_pins = new QLabel(groupBox_vm);
        label_vm_pins->setObjectName(QString::fromUtf8("label_vm_pins"));
        label_vm_pins->setGeometry(QRect(70, 70, 91, 20));
        label_vm_pins->setFont(font4);
        label_vm_pins->setTextFormat(Qt::AutoText);
        groupBox_instr2 = new QGroupBox(centralwidget);
        groupBox_instr2->setObjectName(QString::fromUtf8("groupBox_instr2"));
        groupBox_instr2->setGeometry(QRect(240, 360, 551, 181));
        sizePolicy2.setHeightForWidth(groupBox_instr2->sizePolicy().hasHeightForWidth());
        groupBox_instr2->setSizePolicy(sizePolicy2);
        groupBox_instr2->setFont(font2);
        groupBox_instr2->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        groupBox_pwm = new QGroupBox(groupBox_instr2);
        groupBox_pwm->setObjectName(QString::fromUtf8("groupBox_pwm"));
        groupBox_pwm->setGeometry(QRect(190, 20, 171, 151));
        groupBox_pwm->setFont(font7);
        groupBox_pwm->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,200,180, 0.5);border: 1px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        pushButton_pwm = new QPushButton(groupBox_pwm);
        pushButton_pwm->setObjectName(QString::fromUtf8("pushButton_pwm"));
        pushButton_pwm->setGeometry(QRect(0, 110, 171, 41));
        pushButton_pwm->setFont(font8);
        pushButton_pwm->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/main/resources/img/pwm.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_pwm->setIcon(icon8);
        pushButton_pwm->setIconSize(QSize(21, 21));
        label_19 = new QLabel(groupBox_pwm);
        label_19->setObjectName(QString::fromUtf8("label_19"));
        label_19->setGeometry(QRect(10, 30, 71, 16));
        label_19->setFont(font4);
        label_19->setTextFormat(Qt::AutoText);
        label_35 = new QLabel(groupBox_pwm);
        label_35->setObjectName(QString::fromUtf8("label_35"));
        label_35->setGeometry(QRect(10, 50, 71, 16));
        label_35->setFont(font4);
        label_35->setTextFormat(Qt::AutoText);
        label_pwm_pins = new QLabel(groupBox_pwm);
        label_pwm_pins->setObjectName(QString::fromUtf8("label_pwm_pins"));
        label_pwm_pins->setGeometry(QRect(80, 50, 81, 16));
        label_pwm_pins->setFont(font4);
        label_pwm_pins->setTextFormat(Qt::AutoText);
        label_pwm_freq = new QLabel(groupBox_pwm);
        label_pwm_freq->setObjectName(QString::fromUtf8("label_pwm_freq"));
        label_pwm_freq->setGeometry(QRect(80, 30, 81, 16));
        label_pwm_freq->setFont(font4);
        label_pwm_freq->setTextFormat(Qt::AutoText);
        label_pwm_mode = new QLabel(groupBox_pwm);
        label_pwm_mode->setObjectName(QString::fromUtf8("label_pwm_mode"));
        label_pwm_mode->setGeometry(QRect(80, 10, 81, 20));
        label_pwm_mode->setFont(font4);
        label_pwm_mode->setTextFormat(Qt::AutoText);
        label_33 = new QLabel(groupBox_pwm);
        label_33->setObjectName(QString::fromUtf8("label_33"));
        label_33->setGeometry(QRect(10, 10, 71, 16));
        label_33->setFont(font4);
        label_33->setTextFormat(Qt::AutoText);
        groupBox_sgen = new QGroupBox(groupBox_instr2);
        groupBox_sgen->setObjectName(QString::fromUtf8("groupBox_sgen"));
        groupBox_sgen->setGeometry(QRect(370, 20, 171, 151));
        groupBox_sgen->setFont(font7);
        groupBox_sgen->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,220, 0.5);border: 1px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        pushButton_sgen = new QPushButton(groupBox_sgen);
        pushButton_sgen->setObjectName(QString::fromUtf8("pushButton_sgen"));
        pushButton_sgen->setGeometry(QRect(0, 110, 171, 41));
        pushButton_sgen->setFont(font8);
        pushButton_sgen->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);;\n"
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
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/main/resources/img/sgen2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_sgen->setIcon(icon9);
        pushButton_sgen->setIconSize(QSize(22, 22));
        label_27 = new QLabel(groupBox_sgen);
        label_27->setObjectName(QString::fromUtf8("label_27"));
        label_27->setGeometry(QRect(10, 10, 71, 16));
        label_27->setFont(font4);
        label_27->setTextFormat(Qt::AutoText);
        label_28 = new QLabel(groupBox_sgen);
        label_28->setObjectName(QString::fromUtf8("label_28"));
        label_28->setGeometry(QRect(10, 30, 71, 16));
        label_28->setFont(font4);
        label_28->setTextFormat(Qt::AutoText);
        label_36 = new QLabel(groupBox_sgen);
        label_36->setObjectName(QString::fromUtf8("label_36"));
        label_36->setGeometry(QRect(10, 50, 71, 16));
        label_36->setFont(font4);
        label_36->setTextFormat(Qt::AutoText);
        label_sgen_pins = new QLabel(groupBox_sgen);
        label_sgen_pins->setObjectName(QString::fromUtf8("label_sgen_pins"));
        label_sgen_pins->setGeometry(QRect(90, 50, 71, 16));
        label_sgen_pins->setFont(font4);
        label_sgen_pins->setTextFormat(Qt::AutoText);
        label_sgen_mem = new QLabel(groupBox_sgen);
        label_sgen_mem->setObjectName(QString::fromUtf8("label_sgen_mem"));
        label_sgen_mem->setGeometry(QRect(90, 30, 71, 16));
        label_sgen_mem->setFont(font4);
        label_sgen_mem->setTextFormat(Qt::AutoText);
        label_sgen_freq = new QLabel(groupBox_sgen);
        label_sgen_freq->setObjectName(QString::fromUtf8("label_sgen_freq"));
        label_sgen_freq->setGeometry(QRect(90, 10, 71, 16));
        label_sgen_freq->setFont(font4);
        label_sgen_freq->setTextFormat(Qt::AutoText);
        groupBox_cntr = new QGroupBox(groupBox_instr2);
        groupBox_cntr->setObjectName(QString::fromUtf8("groupBox_cntr"));
        groupBox_cntr->setGeometry(QRect(10, 20, 171, 151));
        groupBox_cntr->setFont(font7);
        groupBox_cntr->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,220,200, 0.5);border: 1px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        pushButton_cntr = new QPushButton(groupBox_cntr);
        pushButton_cntr->setObjectName(QString::fromUtf8("pushButton_cntr"));
        pushButton_cntr->setGeometry(QRect(0, 110, 171, 41));
        pushButton_cntr->setFont(font8);
        pushButton_cntr->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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
        QIcon icon10;
        icon10.addFile(QString::fromUtf8(":/main/resources/img/cntr.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_cntr->setIcon(icon10);
        pushButton_cntr->setIconSize(QSize(21, 21));
        label_37 = new QLabel(groupBox_cntr);
        label_37->setObjectName(QString::fromUtf8("label_37"));
        label_37->setGeometry(QRect(10, 50, 71, 16));
        label_37->setFont(font4);
        label_37->setTextFormat(Qt::AutoText);
        label_32 = new QLabel(groupBox_cntr);
        label_32->setObjectName(QString::fromUtf8("label_32"));
        label_32->setGeometry(QRect(10, 10, 71, 16));
        label_32->setFont(font4);
        label_32->setTextFormat(Qt::AutoText);
        label_34 = new QLabel(groupBox_cntr);
        label_34->setObjectName(QString::fromUtf8("label_34"));
        label_34->setGeometry(QRect(10, 30, 71, 16));
        label_34->setFont(font4);
        label_34->setTextFormat(Qt::AutoText);
        label_cntr_mode = new QLabel(groupBox_cntr);
        label_cntr_mode->setObjectName(QString::fromUtf8("label_cntr_mode"));
        label_cntr_mode->setGeometry(QRect(80, 10, 91, 20));
        label_cntr_mode->setFont(font4);
        label_cntr_mode->setTextFormat(Qt::AutoText);
        label_cntr_pins = new QLabel(groupBox_cntr);
        label_cntr_pins->setObjectName(QString::fromUtf8("label_cntr_pins"));
        label_cntr_pins->setGeometry(QRect(80, 50, 81, 16));
        label_cntr_pins->setFont(font4);
        label_cntr_pins->setTextFormat(Qt::AutoText);
        label_cntr_timeout = new QLabel(groupBox_cntr);
        label_cntr_timeout->setObjectName(QString::fromUtf8("label_cntr_timeout"));
        label_cntr_timeout->setGeometry(QRect(80, 30, 81, 16));
        label_cntr_timeout->setFont(font4);
        label_cntr_timeout->setTextFormat(Qt::AutoText);
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 540, 801, 21));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        WindowMain->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowMain);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 20));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Roboto"));
        font9.setPointSize(9);
        font9.setItalic(false);
        font9.setKerning(true);
        menubar->setFont(font9);
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        WindowMain->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowMain);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        QFont font10;
        font10.setFamily(QString::fromUtf8("Roboto"));
        font10.setPointSize(8);
        font10.setItalic(false);
        font10.setKerning(true);
        statusbar->setFont(font10);
        statusbar->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        WindowMain->setStatusBar(statusbar);

        menubar->addAction(menuAbout->menuAction());
        menuAbout->addAction(actionAbout);

        retranslateUi(WindowMain);

        QMetaObject::connectSlotsByName(WindowMain);
    } // setupUi

    void retranslateUi(QMainWindow *WindowMain)
    {
        WindowMain->setWindowTitle(QCoreApplication::translate("WindowMain", "EMBO - EMBedded Oscilloscope", nullptr));
        actionAbout->setText(QCoreApplication::translate("WindowMain", "About", nullptr));
#if QT_CONFIG(shortcut)
        actionAbout->setShortcut(QCoreApplication::translate("WindowMain", "Ctrl+A", nullptr));
#endif // QT_CONFIG(shortcut)
        actionOpen->setText(QCoreApplication::translate("WindowMain", "Open", nullptr));
#if QT_CONFIG(shortcut)
        actionOpen->setShortcut(QCoreApplication::translate("WindowMain", "Ctrl+O", nullptr));
#endif // QT_CONFIG(shortcut)
        groupBox_ports->setTitle(QCoreApplication::translate("WindowMain", "Ports", nullptr));

        const bool __sortingEnabled = listWidget_ports->isSortingEnabled();
        listWidget_ports->setSortingEnabled(false);
        QListWidgetItem *___qlistwidgetitem = listWidget_ports->item(0);
        ___qlistwidgetitem->setText(QCoreApplication::translate("WindowMain", "COM1", nullptr));
        QListWidgetItem *___qlistwidgetitem1 = listWidget_ports->item(1);
        ___qlistwidgetitem1->setText(QCoreApplication::translate("WindowMain", "COM15", nullptr));
        listWidget_ports->setSortingEnabled(__sortingEnabled);

#if QT_CONFIG(accessibility)
        listWidget_ports->setAccessibleName(QString());
#endif // QT_CONFIG(accessibility)
        pushButton_scan->setText(QCoreApplication::translate("WindowMain", "Scan", nullptr));
        pushButton_connect->setText(QCoreApplication::translate("WindowMain", "Connect", nullptr));
        pushButton_disconnect->setText(QCoreApplication::translate("WindowMain", "Disconnect", nullptr));
        label_cvutlogo->setText(QString());
        groupBox_device->setTitle(QString());
        label_deviceName->setText(QCoreApplication::translate("WindowMain", "NOT CONNECTED", nullptr));
        label_boardImg->setText(QString());
        label->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Firmware version:", nullptr));
        label_2->setText(QCoreApplication::translate("WindowMain", "\342\200\242 STM LL version:", nullptr));
        label_3->setText(QCoreApplication::translate("WindowMain", "\342\200\242 FreeRTOS version:", nullptr));
        label_4->setText(QCoreApplication::translate("WindowMain", "\342\200\242 CPU frequency:", nullptr));
        label_5->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Communication:", nullptr));
        label_dev_fw->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_dev_fcpu->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_dev_comm->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_dev_rtos->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_dev_ll->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_7->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Voltage reference:", nullptr));
        label_dev_vref->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        groupBox_instr1->setTitle(QCoreApplication::translate("WindowMain", "Main Instruments", nullptr));
        groupBox_scope->setTitle(QString());
        pushButton_scope->setText(QCoreApplication::translate("WindowMain", "Oscilloscope", nullptr));
        label_6->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Fs:", nullptr));
        label_8->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Mem:", nullptr));
        label_9->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Bits:", nullptr));
        label_10->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Mode:", nullptr));
        label_40->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Pins:", nullptr));
        label_scope_fs->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_scope_mem->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_scope_bits->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_scope_modes->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_scope_pins->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        groupBox_la->setTitle(QString());
        pushButton_la->setText(QCoreApplication::translate("WindowMain", "Logic Analyzer", nullptr));
        label_11->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Fs:", nullptr));
        label_12->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Mem:", nullptr));
        label_13->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Proto:", nullptr));
        label_39->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Pins:", nullptr));
        label_la_pins->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_la_protocols->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_la_fs->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_la_mem->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        groupBox_vm->setTitle(QString());
        pushButton_vm->setText(QCoreApplication::translate("WindowMain", "Voltmeter", nullptr));
        label_15->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Fs:", nullptr));
        label_16->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Mem:", nullptr));
        label_17->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Bits:", nullptr));
        label_38->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Pins:", nullptr));
        label_vm_fs->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_vm_mem->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_vm_bits->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_vm_pins->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        groupBox_instr2->setTitle(QCoreApplication::translate("WindowMain", "Aux Instruments", nullptr));
        groupBox_pwm->setTitle(QString());
        pushButton_pwm->setText(QCoreApplication::translate("WindowMain", "PWM Generator", nullptr));
        label_19->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Max freq:", nullptr));
        label_35->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Pins:", nullptr));
        label_pwm_pins->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_pwm_freq->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_pwm_mode->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_33->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Mode:", nullptr));
        groupBox_sgen->setTitle(QString());
        pushButton_sgen->setText(QCoreApplication::translate("WindowMain", "Signal Generator", nullptr));
        label_27->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Max freq:", nullptr));
        label_28->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Max mem:", nullptr));
        label_36->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Pin:", nullptr));
        label_sgen_pins->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_sgen_mem->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_sgen_freq->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        groupBox_cntr->setTitle(QString());
        pushButton_cntr->setText(QCoreApplication::translate("WindowMain", "Counter", nullptr));
        label_37->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Pin:", nullptr));
        label_32->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Mode:", nullptr));
        label_34->setText(QCoreApplication::translate("WindowMain", "\342\200\242 Timeout:", nullptr));
        label_cntr_mode->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_cntr_pins->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        label_cntr_timeout->setText(QCoreApplication::translate("WindowMain", "-", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("WindowMain", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowMain: public Ui_WindowMain {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW__MAIN_H
