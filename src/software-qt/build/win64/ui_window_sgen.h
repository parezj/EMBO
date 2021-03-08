/********************************************************************************
** Form generated from reading UI file 'window_sgen.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_SGEN_H
#define UI_WINDOW_SGEN_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDial>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowSgen
{
public:
    QAction *actionAbout;
    QWidget *centralwidget;
    QPushButton *pushButton_disable;
    QPushButton *pushButton_enable;
    QFrame *line;
    QGroupBox *groupBox_1;
    QRadioButton *radioButton_noise;
    QRadioButton *radioButton_triangle;
    QRadioButton *radioButton_const;
    QRadioButton *radioButton_saw;
    QRadioButton *radioButton_sine;
    QRadioButton *radioButton_square;
    QGroupBox *groupBox_2;
    QLabel *label_3;
    QDial *dial_offset;
    QSpinBox *spinBox_ampl;
    QDial *dial_freq;
    QSpinBox *spinBox_offset;
    QDial *dial_ampl;
    QSpinBox *spinBox_freq;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_dial1;
    QLabel *label_dial2;
    QLabel *label_dial3;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowSgen)
    {
        if (WindowSgen->objectName().isEmpty())
            WindowSgen->setObjectName(QString::fromUtf8("WindowSgen"));
        WindowSgen->resize(571, 323);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WindowSgen->sizePolicy().hasHeightForWidth());
        WindowSgen->setSizePolicy(sizePolicy);
        WindowSgen->setMinimumSize(QSize(571, 323));
        WindowSgen->setMaximumSize(QSize(571, 323));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        WindowSgen->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowSgen->setWindowIcon(icon);
        actionAbout = new QAction(WindowSgen);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon1);
        actionAbout->setFont(font);
        centralwidget = new QWidget(WindowSgen);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton_disable = new QPushButton(centralwidget);
        pushButton_disable->setObjectName(QString::fromUtf8("pushButton_disable"));
        pushButton_disable->setGeometry(QRect(200, 220, 171, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(13);
        pushButton_disable->setFont(font1);
        pushButton_disable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"	text-align:left;\n"
"	padding-left:15px;\n"
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
        pushButton_disable->setIcon(icon2);
        pushButton_disable->setIconSize(QSize(23, 22));
        pushButton_enable = new QPushButton(centralwidget);
        pushButton_enable->setObjectName(QString::fromUtf8("pushButton_enable"));
        pushButton_enable->setGeometry(QRect(200, 220, 171, 41));
        pushButton_enable->setFont(font1);
        pushButton_enable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"	text-align:left;\n"
"	padding-left:15px;\n"
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
        icon3.addFile(QString::fromUtf8(":/main/resources/img/power-off-gray2.png"), QSize(), QIcon::Disabled, QIcon::Off);
        pushButton_enable->setIcon(icon3);
        pushButton_enable->setIconSize(QSize(22, 22));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 270, 581, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox_1 = new QGroupBox(centralwidget);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        groupBox_1->setGeometry(QRect(10, 1, 151, 201));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_1->sizePolicy().hasHeightForWidth());
        groupBox_1->setSizePolicy(sizePolicy1);
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto"));
        font2.setPointSize(10);
        font2.setBold(false);
        font2.setItalic(false);
        font2.setWeight(50);
        font2.setKerning(true);
        groupBox_1->setFont(font2);
        groupBox_1->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        radioButton_noise = new QRadioButton(groupBox_1);
        radioButton_noise->setObjectName(QString::fromUtf8("radioButton_noise"));
        radioButton_noise->setGeometry(QRect(10, 170, 131, 21));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Roboto"));
        font3.setPointSize(14);
        radioButton_noise->setFont(font3);
        radioButton_noise->setStyleSheet(QString::fromUtf8("QRadioButton:checked {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:hover {\n"
"	background-color: rgba(230,230,230, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:checked:hover {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}\n"
"QRadioButton::indicator::unchecked {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:hover {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked {\n"
"    image: url(:/main/resources/img/radio_on2.png);\n"
"}"));
        QIcon icon4;
        icon4.addFile(QString::fromUtf8(":/main/resources/img/sgen_noise.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_noise->setIcon(icon4);
        radioButton_noise->setIconSize(QSize(20, 20));
        radioButton_noise->setAutoExclusive(false);
        radioButton_triangle = new QRadioButton(groupBox_1);
        radioButton_triangle->setObjectName(QString::fromUtf8("radioButton_triangle"));
        radioButton_triangle->setGeometry(QRect(10, 80, 131, 21));
        radioButton_triangle->setFont(font3);
        radioButton_triangle->setStyleSheet(QString::fromUtf8("QRadioButton:checked {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:hover {\n"
"	background-color: rgba(230,230,230, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:checked:hover {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}\n"
"QRadioButton::indicator::unchecked {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:hover {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked {\n"
"    image: url(:/main/resources/img/radio_on2.png);\n"
"}"));
        QIcon icon5;
        icon5.addFile(QString::fromUtf8(":/main/resources/img/sgen_triangle.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_triangle->setIcon(icon5);
        radioButton_triangle->setIconSize(QSize(20, 20));
        radioButton_triangle->setAutoExclusive(false);
        radioButton_const = new QRadioButton(groupBox_1);
        radioButton_const->setObjectName(QString::fromUtf8("radioButton_const"));
        radioButton_const->setGeometry(QRect(10, 20, 131, 21));
        radioButton_const->setFont(font3);
        radioButton_const->setStyleSheet(QString::fromUtf8("QRadioButton:checked {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:hover {\n"
"	background-color: rgba(230,230,230, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:checked:hover {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}\n"
"QRadioButton::indicator::unchecked {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:hover {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked {\n"
"    image: url(:/main/resources/img/radio_on2.png);\n"
"}"));
        QIcon icon6;
        icon6.addFile(QString::fromUtf8(":/main/resources/img/sgen_const.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_const->setIcon(icon6);
        radioButton_const->setIconSize(QSize(20, 20));
        radioButton_const->setChecked(false);
        radioButton_const->setAutoExclusive(false);
        radioButton_saw = new QRadioButton(groupBox_1);
        radioButton_saw->setObjectName(QString::fromUtf8("radioButton_saw"));
        radioButton_saw->setGeometry(QRect(10, 110, 131, 21));
        radioButton_saw->setFont(font3);
        radioButton_saw->setStyleSheet(QString::fromUtf8("QRadioButton:checked {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:hover {\n"
"	background-color: rgba(230,230,230, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:checked:hover {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}\n"
"QRadioButton::indicator::unchecked {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:hover {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked {\n"
"    image: url(:/main/resources/img/radio_on2.png);\n"
"}"));
        QIcon icon7;
        icon7.addFile(QString::fromUtf8(":/main/resources/img/sgen_saw.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_saw->setIcon(icon7);
        radioButton_saw->setIconSize(QSize(20, 20));
        radioButton_saw->setAutoExclusive(false);
        radioButton_sine = new QRadioButton(groupBox_1);
        radioButton_sine->setObjectName(QString::fromUtf8("radioButton_sine"));
        radioButton_sine->setGeometry(QRect(10, 50, 131, 21));
        radioButton_sine->setFont(font3);
        radioButton_sine->setStyleSheet(QString::fromUtf8("QRadioButton:checked {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:hover {\n"
"	background-color: rgba(230,230,230, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:checked:hover {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}\n"
"QRadioButton::indicator::unchecked {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:hover {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked {\n"
"    image: url(:/main/resources/img/radio_on2.png);\n"
"}"));
        QIcon icon8;
        icon8.addFile(QString::fromUtf8(":/main/resources/img/sgen_sine.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_sine->setIcon(icon8);
        radioButton_sine->setIconSize(QSize(20, 20));
        radioButton_sine->setChecked(false);
        radioButton_sine->setAutoExclusive(false);
        radioButton_square = new QRadioButton(groupBox_1);
        radioButton_square->setObjectName(QString::fromUtf8("radioButton_square"));
        radioButton_square->setGeometry(QRect(10, 140, 131, 21));
        radioButton_square->setFont(font3);
        radioButton_square->setStyleSheet(QString::fromUtf8("QRadioButton:checked {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:hover {\n"
"	background-color: rgba(230,230,230, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton:checked:hover {\n"
"	background-color: rgba(245,245,245, 1.0);\n"
"	border: 0px; \n"
"	border-radius:5px;\n"
"}\n"
"\n"
"QRadioButton::indicator {\n"
"    width: 20px;\n"
"    height: 20px;\n"
"}\n"
"QRadioButton::indicator::unchecked {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator:unchecked:hover {\n"
"    image: url(:/main/resources/img/radio_off1.png);\n"
"}\n"
"\n"
"QRadioButton::indicator::checked {\n"
"    image: url(:/main/resources/img/radio_on2.png);\n"
"}"));
        QIcon icon9;
        icon9.addFile(QString::fromUtf8(":/main/resources/img/sgen_square.png"), QSize(), QIcon::Normal, QIcon::Off);
        radioButton_square->setIcon(icon9);
        radioButton_square->setIconSize(QSize(20, 20));
        radioButton_square->setAutoExclusive(false);
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(170, 1, 391, 201));
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        groupBox_2->setFont(font2);
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        label_3 = new QLabel(groupBox_2);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 150, 111, 21));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto Light"));
        font4.setPointSize(14);
        font4.setBold(false);
        font4.setWeight(50);
        label_3->setFont(font4);
        dial_offset = new QDial(groupBox_2);
        dial_offset->setObjectName(QString::fromUtf8("dial_offset"));
        dial_offset->setGeometry(QRect(10, 135, 51, 50));
        dial_offset->setMaximum(100);
        dial_offset->setOrientation(Qt::Horizontal);
        dial_offset->setInvertedAppearance(false);
        dial_offset->setWrapping(false);
        dial_offset->setNotchesVisible(true);
        spinBox_ampl = new QSpinBox(groupBox_2);
        spinBox_ampl->setObjectName(QString::fromUtf8("spinBox_ampl"));
        spinBox_ampl->setGeometry(QRect(70, 80, 301, 41));
        spinBox_ampl->setStyleSheet(QString::fromUtf8("QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px;\n"
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
        spinBox_ampl->setWrapping(false);
        spinBox_ampl->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_ampl->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox_ampl->setAccelerated(false);
        spinBox_ampl->setKeyboardTracking(false);
        spinBox_ampl->setProperty("showGroupSeparator", QVariant(false));
        spinBox_ampl->setMaximum(100);
        spinBox_ampl->setValue(50);
        dial_freq = new QDial(groupBox_2);
        dial_freq->setObjectName(QString::fromUtf8("dial_freq"));
        dial_freq->setGeometry(QRect(10, 15, 51, 50));
        dial_freq->setStyleSheet(QString::fromUtf8(""));
        dial_freq->setOrientation(Qt::Horizontal);
        dial_freq->setInvertedAppearance(false);
        dial_freq->setWrapping(false);
        dial_freq->setNotchesVisible(true);
        spinBox_offset = new QSpinBox(groupBox_2);
        spinBox_offset->setObjectName(QString::fromUtf8("spinBox_offset"));
        spinBox_offset->setGeometry(QRect(70, 140, 301, 41));
        spinBox_offset->setStyleSheet(QString::fromUtf8("QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px;\n"
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
        spinBox_offset->setWrapping(false);
        spinBox_offset->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_offset->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox_offset->setAccelerated(false);
        spinBox_offset->setKeyboardTracking(false);
        spinBox_offset->setProperty("showGroupSeparator", QVariant(false));
        spinBox_offset->setMaximum(100);
        spinBox_offset->setValue(50);
        dial_ampl = new QDial(groupBox_2);
        dial_ampl->setObjectName(QString::fromUtf8("dial_ampl"));
        dial_ampl->setGeometry(QRect(10, 75, 51, 50));
        dial_ampl->setMaximum(100);
        dial_ampl->setOrientation(Qt::Horizontal);
        dial_ampl->setInvertedAppearance(false);
        dial_ampl->setWrapping(false);
        dial_ampl->setNotchesVisible(true);
        spinBox_freq = new QSpinBox(groupBox_2);
        spinBox_freq->setObjectName(QString::fromUtf8("spinBox_freq"));
        spinBox_freq->setGeometry(QRect(70, 20, 301, 41));
        spinBox_freq->setStyleSheet(QString::fromUtf8("QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px;\n"
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
        spinBox_freq->setWrapping(false);
        spinBox_freq->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_freq->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox_freq->setAccelerated(false);
        spinBox_freq->setKeyboardTracking(false);
        spinBox_freq->setProperty("showGroupSeparator", QVariant(false));
        spinBox_freq->setMaximum(5000000);
        spinBox_freq->setValue(5000000);
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 30, 111, 21));
        label->setFont(font4);
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 90, 111, 21));
        label_2->setFont(font4);
        label_dial1 = new QLabel(groupBox_2);
        label_dial1->setObjectName(QString::fromUtf8("label_dial1"));
        label_dial1->setGeometry(QRect(10, 15, 51, 50));
        label_dial1->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial1->setScaledContents(false);
        label_dial2 = new QLabel(groupBox_2);
        label_dial2->setObjectName(QString::fromUtf8("label_dial2"));
        label_dial2->setGeometry(QRect(10, 75, 51, 50));
        label_dial2->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial2->setScaledContents(false);
        label_dial3 = new QLabel(groupBox_2);
        label_dial3->setObjectName(QString::fromUtf8("label_dial3"));
        label_dial3->setGeometry(QRect(10, 135, 51, 50));
        label_dial3->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial3->setScaledContents(false);
        spinBox_ampl->raise();
        spinBox_offset->raise();
        spinBox_freq->raise();
        label->raise();
        label_2->raise();
        label_3->raise();
        label_dial1->raise();
        label_dial3->raise();
        label_dial2->raise();
        dial_ampl->raise();
        dial_offset->raise();
        dial_freq->raise();
        WindowSgen->setCentralWidget(centralwidget);
        pushButton_enable->raise();
        line->raise();
        groupBox_1->raise();
        groupBox_2->raise();
        pushButton_disable->raise();
        menubar = new QMenuBar(WindowSgen);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 571, 21));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuHelp->setFont(font);
        WindowSgen->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowSgen);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        WindowSgen->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(WindowSgen);

        QMetaObject::connectSlotsByName(WindowSgen);
    } // setupUi

    void retranslateUi(QMainWindow *WindowSgen)
    {
        WindowSgen->setWindowTitle(QCoreApplication::translate("WindowSgen", "EMBO - Signal Generator", nullptr));
        actionAbout->setText(QCoreApplication::translate("WindowSgen", "About", nullptr));
        pushButton_disable->setText(QCoreApplication::translate("WindowSgen", " Generator ON  ", nullptr));
        pushButton_enable->setText(QCoreApplication::translate("WindowSgen", " Generator OFF", nullptr));
        groupBox_1->setTitle(QString());
        radioButton_noise->setText(QCoreApplication::translate("WindowSgen", "Noise", nullptr));
        radioButton_triangle->setText(QCoreApplication::translate("WindowSgen", "Triangle", nullptr));
        radioButton_const->setText(QCoreApplication::translate("WindowSgen", "Constant", nullptr));
        radioButton_saw->setText(QCoreApplication::translate("WindowSgen", "Sawtooth", nullptr));
        radioButton_sine->setText(QCoreApplication::translate("WindowSgen", "Sine", nullptr));
        radioButton_square->setText(QCoreApplication::translate("WindowSgen", "Square", nullptr));
        groupBox_2->setTitle(QString());
        label_3->setText(QCoreApplication::translate("WindowSgen", "Offset:", nullptr));
        spinBox_ampl->setSuffix(QCoreApplication::translate("WindowSgen", " %", nullptr));
        spinBox_offset->setSuffix(QCoreApplication::translate("WindowSgen", " %", nullptr));
        spinBox_freq->setSuffix(QCoreApplication::translate("WindowSgen", " Hz", nullptr));
        label->setText(QCoreApplication::translate("WindowSgen", "Frequency:", nullptr));
        label_2->setText(QCoreApplication::translate("WindowSgen", "Amplitude:", nullptr));
        label_dial1->setText(QString());
        label_dial2->setText(QString());
        label_dial3->setText(QString());
        menuHelp->setTitle(QCoreApplication::translate("WindowSgen", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowSgen: public Ui_WindowSgen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_SGEN_H
