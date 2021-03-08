/********************************************************************************
** Form generated from reading UI file 'window_pwm.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_PWM_H
#define UI_WINDOW_PWM_H

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
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowPwm
{
public:
    QAction *actionAbout;
    QWidget *centralwidget;
    QFrame *line;
    QPushButton *pushButton_ch1enable;
    QPushButton *pushButton_ch1disable;
    QPushButton *pushButton_ch2enable;
    QPushButton *pushButton_ch2disable;
    QGroupBox *groupBox_1;
    QDial *dial_freq;
    QLabel *label_4;
    QSpinBox *spinBox_freq;
    QLabel *label_dial1;
    QRadioButton *radioButton_coarse;
    QTextBrowser *textBrowser_realFreq;
    QLabel *label_5;
    QGroupBox *groupBox_2;
    QLabel *label_2;
    QLabel *label;
    QSpinBox *spinBox_duty1;
    QSpinBox *spinBox_duty2;
    QDial *dial_duty2;
    QDial *dial_duty1;
    QLabel *label_dial2;
    QLabel *label_dial3;
    QGroupBox *groupBox_3;
    QLabel *label_3;
    QDial *dial_offset;
    QSpinBox *spinBox_offset;
    QLabel *label_dial4;
    QRadioButton *radioButton_fine;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowPwm)
    {
        if (WindowPwm->objectName().isEmpty())
            WindowPwm->setObjectName(QString::fromUtf8("WindowPwm"));
        WindowPwm->resize(411, 463);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WindowPwm->sizePolicy().hasHeightForWidth());
        WindowPwm->setSizePolicy(sizePolicy);
        WindowPwm->setMinimumSize(QSize(411, 463));
        WindowPwm->setMaximumSize(QSize(411, 463));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        WindowPwm->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowPwm->setWindowIcon(icon);
        actionAbout = new QAction(WindowPwm);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon1);
        actionAbout->setFont(font);
        centralwidget = new QWidget(WindowPwm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 410, 431, 16));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        pushButton_ch1enable = new QPushButton(centralwidget);
        pushButton_ch1enable->setObjectName(QString::fromUtf8("pushButton_ch1enable"));
        pushButton_ch1enable->setGeometry(QRect(40, 355, 151, 41));
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(13);
        font1.setKerning(true);
        pushButton_ch1enable->setFont(font1);
        pushButton_ch1enable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
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
"	border: 2px solid rgb(150, 150, 150);;\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-gray2.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-gray2.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-gray2.png"), QSize(), QIcon::Disabled, QIcon::On);
        pushButton_ch1enable->setIcon(icon2);
        pushButton_ch1enable->setIconSize(QSize(22, 22));
        pushButton_ch1disable = new QPushButton(centralwidget);
        pushButton_ch1disable->setObjectName(QString::fromUtf8("pushButton_ch1disable"));
        pushButton_ch1disable->setGeometry(QRect(40, 355, 151, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto"));
        font2.setPointSize(13);
        font2.setBold(false);
        font2.setWeight(50);
        font2.setKerning(true);
        pushButton_ch1disable->setFont(font2);
        pushButton_ch1disable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
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
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Disabled, QIcon::Off);
        pushButton_ch1disable->setIcon(icon3);
        pushButton_ch1disable->setIconSize(QSize(23, 22));
        pushButton_ch2enable = new QPushButton(centralwidget);
        pushButton_ch2enable->setObjectName(QString::fromUtf8("pushButton_ch2enable"));
        pushButton_ch2enable->setGeometry(QRect(220, 355, 151, 41));
        pushButton_ch2enable->setFont(font1);
        pushButton_ch2enable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
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
        pushButton_ch2enable->setIcon(icon2);
        pushButton_ch2enable->setIconSize(QSize(22, 22));
        pushButton_ch2disable = new QPushButton(centralwidget);
        pushButton_ch2disable->setObjectName(QString::fromUtf8("pushButton_ch2disable"));
        pushButton_ch2disable->setEnabled(true);
        pushButton_ch2disable->setGeometry(QRect(220, 355, 151, 41));
        pushButton_ch2disable->setFont(font2);
        pushButton_ch2disable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
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
        pushButton_ch2disable->setIcon(icon3);
        pushButton_ch2disable->setIconSize(QSize(23, 22));
        groupBox_1 = new QGroupBox(centralwidget);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        groupBox_1->setGeometry(QRect(10, 1, 391, 120));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_1->sizePolicy().hasHeightForWidth());
        groupBox_1->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Roboto"));
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        font3.setKerning(true);
        groupBox_1->setFont(font3);
        groupBox_1->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        dial_freq = new QDial(groupBox_1);
        dial_freq->setObjectName(QString::fromUtf8("dial_freq"));
        dial_freq->setEnabled(true);
        dial_freq->setGeometry(QRect(10, 15, 51, 50));
        QPalette palette;
        dial_freq->setPalette(palette);
        dial_freq->setAutoFillBackground(false);
        dial_freq->setStyleSheet(QString::fromUtf8(""));
        dial_freq->setMinimum(1);
        dial_freq->setMaximum(5000000);
        dial_freq->setOrientation(Qt::Horizontal);
        dial_freq->setInvertedAppearance(false);
        dial_freq->setInvertedControls(false);
        dial_freq->setWrapping(false);
        dial_freq->setNotchTarget(30.000000000000000);
        dial_freq->setNotchesVisible(true);
        label_4 = new QLabel(groupBox_1);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(80, 30, 111, 21));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto Light"));
        font4.setPointSize(14);
        font4.setBold(false);
        font4.setWeight(50);
        label_4->setFont(font4);
        spinBox_freq = new QSpinBox(groupBox_1);
        spinBox_freq->setObjectName(QString::fromUtf8("spinBox_freq"));
        spinBox_freq->setEnabled(true);
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
        spinBox_freq->setMinimum(1);
        spinBox_freq->setMaximum(5000000);
        spinBox_freq->setValue(5000000);
        label_dial1 = new QLabel(groupBox_1);
        label_dial1->setObjectName(QString::fromUtf8("label_dial1"));
        label_dial1->setGeometry(QRect(10, 15, 51, 50));
        label_dial1->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial1->setScaledContents(false);
        radioButton_coarse = new QRadioButton(groupBox_1);
        radioButton_coarse->setObjectName(QString::fromUtf8("radioButton_coarse"));
        radioButton_coarse->setGeometry(QRect(7, 69, 61, 16));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Roboto Light"));
        font5.setPointSize(10);
        radioButton_coarse->setFont(font5);
        radioButton_coarse->setStyleSheet(QString::fromUtf8("QRadioButton:checked {\n"
"	background-color: rgba(245,245,245, 0.0);\n"
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
"    width: 13px;\n"
"    height: 13px;\n"
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
        radioButton_coarse->setIconSize(QSize(20, 20));
        radioButton_coarse->setChecked(false);
        radioButton_coarse->setAutoExclusive(false);
        textBrowser_realFreq = new QTextBrowser(groupBox_1);
        textBrowser_realFreq->setObjectName(QString::fromUtf8("textBrowser_realFreq"));
        textBrowser_realFreq->setEnabled(true);
        textBrowser_realFreq->setGeometry(QRect(70, 69, 301, 36));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(textBrowser_realFreq->sizePolicy().hasHeightForWidth());
        textBrowser_realFreq->setSizePolicy(sizePolicy2);
        QFont font6;
        font6.setFamily(QString::fromUtf8("Roboto Mono Light"));
        font6.setPointSize(14);
        font6.setBold(false);
        font6.setItalic(false);
        font6.setWeight(50);
        textBrowser_realFreq->setFont(font6);
        textBrowser_realFreq->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_realFreq->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Light','Roboto'; font-size:14pt; font-weight:400;\n"
"	color:black; \n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Light','Roboto'; font-size:14pt; font-weight:400;\n"
"	color:black;\n"
"}"));
        label_5 = new QLabel(groupBox_1);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(80, 77, 91, 21));
        QFont font7;
        font7.setFamily(QString::fromUtf8("Roboto Light"));
        font7.setPointSize(13);
        font7.setBold(false);
        font7.setWeight(50);
        label_5->setFont(font7);
        spinBox_freq->raise();
        label_4->raise();
        label_dial1->raise();
        dial_freq->raise();
        radioButton_coarse->raise();
        textBrowser_realFreq->raise();
        label_5->raise();
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(10, 122, 391, 135));
        sizePolicy1.setHeightForWidth(groupBox_2->sizePolicy().hasHeightForWidth());
        groupBox_2->setSizePolicy(sizePolicy1);
        groupBox_2->setFont(font3);
        groupBox_2->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        label_2 = new QLabel(groupBox_2);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(80, 90, 111, 21));
        label_2->setFont(font4);
        label = new QLabel(groupBox_2);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(80, 30, 111, 21));
        label->setFont(font4);
        spinBox_duty1 = new QSpinBox(groupBox_2);
        spinBox_duty1->setObjectName(QString::fromUtf8("spinBox_duty1"));
        spinBox_duty1->setGeometry(QRect(70, 20, 301, 41));
        spinBox_duty1->setStyleSheet(QString::fromUtf8("QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px;\n"
"				   text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;  }\n"
"\n"
"QSpinBox::up-button { height:22px; width: 30px; border: 0px;\n"
"									 image: url(:/main/resources/img/arrow_up4.png); }\n"
"\n"
"QSpinBox::down-button { height:22px; width: 30px; border: 0px;\n"
"										  image: url(:/main/resources/img/arrow_down4.png); }\n"
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
"                                          text-align:right;font-family:'Roboto Mono Medium','Rob"
                        "oto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QSpinBox::up-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
"\n"
"QSpinBox::down-button:disabled { height:22px; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_down2.png); }\n"
""));
        spinBox_duty1->setWrapping(false);
        spinBox_duty1->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_duty1->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox_duty1->setAccelerated(false);
        spinBox_duty1->setKeyboardTracking(false);
        spinBox_duty1->setProperty("showGroupSeparator", QVariant(false));
        spinBox_duty1->setMaximum(100);
        spinBox_duty1->setValue(50);
        spinBox_duty2 = new QSpinBox(groupBox_2);
        spinBox_duty2->setObjectName(QString::fromUtf8("spinBox_duty2"));
        spinBox_duty2->setGeometry(QRect(70, 80, 301, 41));
        spinBox_duty2->setStyleSheet(QString::fromUtf8("QSpinBox { background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px;\n"
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
        spinBox_duty2->setWrapping(false);
        spinBox_duty2->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);
        spinBox_duty2->setButtonSymbols(QAbstractSpinBox::UpDownArrows);
        spinBox_duty2->setAccelerated(false);
        spinBox_duty2->setKeyboardTracking(false);
        spinBox_duty2->setProperty("showGroupSeparator", QVariant(false));
        spinBox_duty2->setMaximum(100);
        spinBox_duty2->setValue(50);
        dial_duty2 = new QDial(groupBox_2);
        dial_duty2->setObjectName(QString::fromUtf8("dial_duty2"));
        dial_duty2->setGeometry(QRect(10, 75, 51, 50));
        dial_duty2->setMaximum(100);
        dial_duty2->setValue(100);
        dial_duty2->setOrientation(Qt::Horizontal);
        dial_duty2->setInvertedAppearance(false);
        dial_duty2->setWrapping(false);
        dial_duty2->setNotchTarget(5.000000000000000);
        dial_duty2->setNotchesVisible(true);
        dial_duty1 = new QDial(groupBox_2);
        dial_duty1->setObjectName(QString::fromUtf8("dial_duty1"));
        dial_duty1->setEnabled(false);
        dial_duty1->setGeometry(QRect(10, 15, 51, 50));
        dial_duty1->setMaximum(100);
        dial_duty1->setOrientation(Qt::Horizontal);
        dial_duty1->setInvertedAppearance(false);
        dial_duty1->setWrapping(false);
        dial_duty1->setNotchTarget(5.000000000000000);
        dial_duty1->setNotchesVisible(true);
        label_dial2 = new QLabel(groupBox_2);
        label_dial2->setObjectName(QString::fromUtf8("label_dial2"));
        label_dial2->setGeometry(QRect(10, 15, 51, 50));
        label_dial2->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial2->setScaledContents(false);
        label_dial3 = new QLabel(groupBox_2);
        label_dial3->setObjectName(QString::fromUtf8("label_dial3"));
        label_dial3->setGeometry(QRect(10, 75, 51, 50));
        label_dial3->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial3->setScaledContents(false);
        spinBox_duty1->raise();
        spinBox_duty2->raise();
        label_2->raise();
        label->raise();
        label_dial2->raise();
        label_dial3->raise();
        dial_duty1->raise();
        dial_duty2->raise();
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 259, 391, 75));
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        groupBox_3->setFont(font3);
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        label_3 = new QLabel(groupBox_3);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 30, 111, 21));
        label_3->setFont(font4);
        dial_offset = new QDial(groupBox_3);
        dial_offset->setObjectName(QString::fromUtf8("dial_offset"));
        dial_offset->setGeometry(QRect(10, 15, 51, 50));
        dial_offset->setMaximum(100);
        dial_offset->setOrientation(Qt::Horizontal);
        dial_offset->setInvertedAppearance(false);
        dial_offset->setWrapping(false);
        dial_offset->setNotchTarget(5.000000000000000);
        dial_offset->setNotchesVisible(true);
        spinBox_offset = new QSpinBox(groupBox_3);
        spinBox_offset->setObjectName(QString::fromUtf8("spinBox_offset"));
        spinBox_offset->setGeometry(QRect(70, 20, 301, 41));
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
        label_dial4 = new QLabel(groupBox_3);
        label_dial4->setObjectName(QString::fromUtf8("label_dial4"));
        label_dial4->setGeometry(QRect(10, 15, 51, 50));
        label_dial4->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial4->setScaledContents(false);
        spinBox_offset->raise();
        label_3->raise();
        label_dial4->raise();
        dial_offset->raise();
        radioButton_fine = new QRadioButton(centralwidget);
        radioButton_fine->setObjectName(QString::fromUtf8("radioButton_fine"));
        radioButton_fine->setGeometry(QRect(17, 87, 61, 16));
        radioButton_fine->setFont(font5);
        radioButton_fine->setStyleSheet(QString::fromUtf8("QRadioButton:checked {\n"
"	background-color: rgba(245,245,245, 0.0);\n"
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
"    width: 13px;\n"
"    height: 13px;\n"
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
        radioButton_fine->setIconSize(QSize(20, 20));
        radioButton_fine->setChecked(true);
        radioButton_fine->setAutoExclusive(false);
        WindowPwm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowPwm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 411, 21));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        WindowPwm->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowPwm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        WindowPwm->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(WindowPwm);

        QMetaObject::connectSlotsByName(WindowPwm);
    } // setupUi

    void retranslateUi(QMainWindow *WindowPwm)
    {
        WindowPwm->setWindowTitle(QCoreApplication::translate("WindowPwm", "EMBO - PWM Generator", nullptr));
        actionAbout->setText(QCoreApplication::translate("WindowPwm", "About", nullptr));
        pushButton_ch1enable->setText(QCoreApplication::translate("WindowPwm", " PWM 1 OFF", nullptr));
        pushButton_ch1disable->setText(QCoreApplication::translate("WindowPwm", " PWM 1 ON  ", nullptr));
        pushButton_ch2enable->setText(QCoreApplication::translate("WindowPwm", " PWM 2 OFF", nullptr));
        pushButton_ch2disable->setText(QCoreApplication::translate("WindowPwm", " PWM 2 ON  ", nullptr));
        groupBox_1->setTitle(QString());
        label_4->setText(QCoreApplication::translate("WindowPwm", "Frequency:", nullptr));
        spinBox_freq->setSuffix(QCoreApplication::translate("WindowPwm", " Hz", nullptr));
        label_dial1->setText(QString());
        radioButton_coarse->setText(QCoreApplication::translate("WindowPwm", "Coarse", nullptr));
        textBrowser_realFreq->setHtml(QCoreApplication::translate("WindowPwm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Light','Roboto'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Light','Roboto Mono Light'; font-weight:496;\">5000000.000 Hz  </span></p></body></html>", nullptr));
        label_5->setText(QCoreApplication::translate("WindowPwm", "Real freq.:", nullptr));
        groupBox_2->setTitle(QString());
        label_2->setText(QCoreApplication::translate("WindowPwm", "Duty Ch2:", nullptr));
        label->setText(QCoreApplication::translate("WindowPwm", "Duty Ch1:", nullptr));
        spinBox_duty1->setSuffix(QCoreApplication::translate("WindowPwm", " %", nullptr));
        spinBox_duty2->setSuffix(QCoreApplication::translate("WindowPwm", " %", nullptr));
        label_dial2->setText(QString());
        label_dial3->setText(QString());
        groupBox_3->setTitle(QString());
        label_3->setText(QCoreApplication::translate("WindowPwm", "Offset Ch2:", nullptr));
        spinBox_offset->setSuffix(QCoreApplication::translate("WindowPwm", " %", nullptr));
        label_dial4->setText(QString());
        radioButton_fine->setText(QCoreApplication::translate("WindowPwm", "Fine", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("WindowPwm", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowPwm: public Ui_WindowPwm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_PWM_H
