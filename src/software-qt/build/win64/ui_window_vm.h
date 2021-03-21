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
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "lib/ctkrangeslider.h"
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
    QAction *actionEnabled;
    QAction *actionReset;
    QAction *actionChannel_1;
    QAction *actionChannel_2;
    QAction *actionChannel_3;
    QAction *actionChannel_4;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox_main;
    QGridLayout *gridLayout_2;
    QGridLayout *gridLayout_plot;
    QSlider *horizontalSlider_trigVal;
    ctkRangeSlider *horizontalSlider_cursorH;
    ctkRangeSlider *horizontalSlider_cursorV;
    QCustomPlot *customPlot;
    QSlider *horizontalSlider_trigPre;
    QGridLayout *gridLayout_3;
    QGroupBox *groupBox_ch4_2;
    QLabel *label_8;
    QTextBrowser *textBrowser_measVpp;
    QLabel *label_9;
    QTextBrowser *textBrowser_measMax;
    QTextBrowser *textBrowser_measMin;
    QTextBrowser *textBrowser_measAvg;
    QLabel *label_11;
    QLabel *label_10;
    QLabel *label_meas;
    QLabel *label_meas_2;
    QGroupBox *groupBox_ch4_3;
    QPushButton *pushButton_cursorsVoff;
    QPushButton *pushButton_cursorsVon;
    QPushButton *pushButton_cursorsHoff;
    QPushButton *pushButton_cursorsHon;
    QGroupBox *groupBox_rightPanel;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_ch1;
    QTextBrowser *textBrowser_ch1;
    QDoubleSpinBox *doubleSpinBox_gain1;
    QLabel *label_7;
    QPushButton *pushButton_disable1;
    QPushButton *pushButton_enable1;
    QLabel *label_ch1;
    QProgressBar *progressBar_ch1;
    QGroupBox *groupBox_ch2;
    QTextBrowser *textBrowser_ch2;
    QDoubleSpinBox *doubleSpinBox_gain2;
    QLabel *label_6;
    QPushButton *pushButton_disable2;
    QPushButton *pushButton_enable2;
    QLabel *label_ch2;
    QProgressBar *progressBar_ch2;
    QGroupBox *groupBox_ch3;
    QTextBrowser *textBrowser_ch3;
    QDoubleSpinBox *doubleSpinBox_gain3;
    QLabel *label_5;
    QPushButton *pushButton_disable3;
    QPushButton *pushButton_enable3;
    QLabel *label_ch3;
    QProgressBar *progressBar_ch3;
    QGroupBox *groupBox_ch4;
    QTextBrowser *textBrowser_ch4;
    QDoubleSpinBox *doubleSpinBox_gain4;
    QLabel *label_4;
    QPushButton *pushButton_enable4;
    QPushButton *pushButton_disable4;
    QLabel *label_ch4;
    QProgressBar *progressBar_ch4;
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
    QMenuBar *menubar;
    QMenu *menuHelp;
    QMenu *menuRecord;
    QMenu *menuFormat;
    QMenu *menuView;
    QMenu *menuInterpolation;
    QMenu *menuMeasure;
    QMenu *menuChannel;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowVm)
    {
        if (WindowVm->objectName().isEmpty())
            WindowVm->setObjectName(QString::fromUtf8("WindowVm"));
        WindowVm->resize(1245, 649);
        WindowVm->setMinimumSize(QSize(940, 648));
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
        actionLinear->setChecked(false);
        actionLinear->setFont(font);
        actionSinc = new QAction(WindowVm);
        actionSinc->setObjectName(QString::fromUtf8("actionSinc"));
        actionSinc->setCheckable(true);
        actionSinc->setChecked(true);
        actionSinc->setEnabled(true);
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
        actionMax->setFont(font);
        actionMin = new QAction(WindowVm);
        actionMin->setObjectName(QString::fromUtf8("actionMin"));
        actionMin->setCheckable(true);
        actionMin->setFont(font);
        actionEnabled = new QAction(WindowVm);
        actionEnabled->setObjectName(QString::fromUtf8("actionEnabled"));
        actionEnabled->setCheckable(true);
        actionEnabled->setChecked(true);
        actionEnabled->setFont(font);
        actionReset = new QAction(WindowVm);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        actionReset->setFont(font);
        actionChannel_1 = new QAction(WindowVm);
        actionChannel_1->setObjectName(QString::fromUtf8("actionChannel_1"));
        actionChannel_1->setCheckable(true);
        actionChannel_1->setChecked(true);
        actionChannel_1->setFont(font);
        actionChannel_2 = new QAction(WindowVm);
        actionChannel_2->setObjectName(QString::fromUtf8("actionChannel_2"));
        actionChannel_2->setCheckable(true);
        actionChannel_2->setFont(font);
        actionChannel_3 = new QAction(WindowVm);
        actionChannel_3->setObjectName(QString::fromUtf8("actionChannel_3"));
        actionChannel_3->setCheckable(true);
        actionChannel_3->setFont(font);
        actionChannel_4 = new QAction(WindowVm);
        actionChannel_4->setObjectName(QString::fromUtf8("actionChannel_4"));
        actionChannel_4->setCheckable(true);
        actionChannel_4->setFont(font);
        centralwidget = new QWidget(WindowVm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        centralwidget->setMinimumSize(QSize(940, 606));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox_main = new QGroupBox(centralwidget);
        groupBox_main->setObjectName(QString::fromUtf8("groupBox_main"));
        groupBox_main->setMinimumSize(QSize(0, 100));
        groupBox_main->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.0em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        gridLayout_2 = new QGridLayout(groupBox_main);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setVerticalSpacing(3);
        gridLayout_plot = new QGridLayout();
        gridLayout_plot->setSpacing(0);
        gridLayout_plot->setObjectName(QString::fromUtf8("gridLayout_plot"));
        horizontalSlider_trigVal = new QSlider(groupBox_main);
        horizontalSlider_trigVal->setObjectName(QString::fromUtf8("horizontalSlider_trigVal"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horizontalSlider_trigVal->sizePolicy().hasHeightForWidth());
        horizontalSlider_trigVal->setSizePolicy(sizePolicy);
        horizontalSlider_trigVal->setMinimumSize(QSize(25, 0));
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        horizontalSlider_trigVal->setFont(font1);
        horizontalSlider_trigVal->setStyleSheet(QString::fromUtf8("ctkRangeSlider {\n"
"    min-width: 25px;\n"
"    max-width: 25px;\n"
"	margin-bottom: 16px;\n"
"	margin-top: 2px;\n"
"}\n"
"\n"
"ctkRangeSlider::groove:vertical {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"ctkRangeSlider::handle:vertical {\n"
"     height: 25px;\n"
"	 image: url(:/main/resources/img/range_right.png);\n"
"}\n"
"\n"
"ctkRangeSlider::handle:vertical:hover {\n"
"     height: 25px;\n"
"	 image: url(:/main/resources/img/range_down2.png);\n"
"}\n"
"\n"
"QSlider {\n"
"    min-width: 25px;\n"
"    max-width: 25px;\n"
"	margin-bottom: 16px;\n"
"	margin-top: 2px;\n"
"}\n"
"\n"
"QSlider::groove:vertical {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QSlider::handle:vertical {\n"
"     height: 25px;\n"
"	 image: url(:/main/resources/img/range_right.png);\n"
"}\n"
"\n"
"QSlider::handle:vertical:hover {\n"
"	 height: 25px;\n"
"	 image: url(:/main/resources/img/range_right2.png);\n"
"}"));
        horizontalSlider_trigVal->setMaximum(1000);
        horizontalSlider_trigVal->setValue(500);
        horizontalSlider_trigVal->setOrientation(Qt::Vertical);
        horizontalSlider_trigVal->setTickPosition(QSlider::NoTicks);
        horizontalSlider_trigVal->setTickInterval(100000);

        gridLayout_plot->addWidget(horizontalSlider_trigVal, 1, 2, 1, 1);

        horizontalSlider_cursorH = new ctkRangeSlider(groupBox_main);
        horizontalSlider_cursorH->setObjectName(QString::fromUtf8("horizontalSlider_cursorH"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(horizontalSlider_cursorH->sizePolicy().hasHeightForWidth());
        horizontalSlider_cursorH->setSizePolicy(sizePolicy1);
        horizontalSlider_cursorH->setMinimumSize(QSize(0, 25));
        horizontalSlider_cursorH->setFont(font1);
        horizontalSlider_cursorH->setStyleSheet(QString::fromUtf8("ctkRangeSlider {\n"
"    min-height: 25px;\n"
"    max-height: 25px;\n"
"	margin-left: 33px;\n"
"	margin-right:2px;\n"
"}\n"
"\n"
"ctkRangeSlider::groove:horizontal {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"ctkRangeSlider::handle:horizontal {\n"
"     width: 25px;\n"
"	 image: url(:/main/resources/img/range_down.png);\n"
"}\n"
"\n"
"ctkRangeSlider::handle:horizontal:hover {\n"
"     width: 25px;\n"
"	 image: url(:/main/resources/img/range_down2.png);\n"
"}\n"
"\n"
"QSlider {\n"
"    min-height: 25px;\n"
"    max-height: 25px;\n"
"	margin-left: 33px;\n"
"	margin-right:2px;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"     width: 25px;\n"
"	 image: url(:/main/resources/img/range_down.png);\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"	 width: 25px;\n"
"	 image: url(:/main/resources/img/range_down2.png);\n"
"}"));
        horizontalSlider_cursorH->setMaximum(1000);
        horizontalSlider_cursorH->setSingleStep(1);
        horizontalSlider_cursorH->setValue(500);
        horizontalSlider_cursorH->setSliderPosition(500);
        horizontalSlider_cursorH->setOrientation(Qt::Horizontal);
        horizontalSlider_cursorH->setTickPosition(QSlider::NoTicks);
        horizontalSlider_cursorH->setTickInterval(100000);

        gridLayout_plot->addWidget(horizontalSlider_cursorH, 2, 1, 1, 1);

        horizontalSlider_cursorV = new ctkRangeSlider(groupBox_main);
        horizontalSlider_cursorV->setObjectName(QString::fromUtf8("horizontalSlider_cursorV"));
        sizePolicy.setHeightForWidth(horizontalSlider_cursorV->sizePolicy().hasHeightForWidth());
        horizontalSlider_cursorV->setSizePolicy(sizePolicy);
        horizontalSlider_cursorV->setMinimumSize(QSize(25, 0));
        horizontalSlider_cursorV->setFont(font1);
        horizontalSlider_cursorV->setStyleSheet(QString::fromUtf8("ctkRangeSlider {\n"
"    min-width: 25px;\n"
"    max-width: 25px;\n"
"	margin-bottom: 16px;\n"
"	margin-top: 2px;\n"
"}\n"
"\n"
"ctkRangeSlider::groove:vertical {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"ctkRangeSlider::handle:vertical {\n"
"     height: 25px;\n"
"	 image: url(:/main/resources/img/range_down.png);\n"
"}\n"
"\n"
"ctkRangeSlider::handle:vertical:hover {\n"
"     height: 25px;\n"
"	 image: url(:/main/resources/img/range_down2.png);\n"
"}\n"
"\n"
"QSlider {\n"
"    min-width: 25px;\n"
"    max-width: 25px;\n"
"	margin-bottom: 16px;\n"
"	margin-top: 2px;\n"
"}\n"
"\n"
"QSlider::groove:vertical {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QSlider::handle:vertical {\n"
"     height: 25px;\n"
"	 image: url(:/main/resources/img/range_left.png);\n"
"}\n"
"\n"
"QSlider::handle:vertical:hover {\n"
"	 height: 25px;\n"
"	 image: url(:/main/resources/img/range_left2.png);\n"
"}"));
        horizontalSlider_cursorV->setMaximum(1000);
        horizontalSlider_cursorV->setValue(500);
        horizontalSlider_cursorV->setOrientation(Qt::Vertical);
        horizontalSlider_cursorV->setTickPosition(QSlider::NoTicks);
        horizontalSlider_cursorV->setTickInterval(100000);

        gridLayout_plot->addWidget(horizontalSlider_cursorV, 1, 0, 1, 1);

        customPlot = new QCustomPlot(groupBox_main);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy2);
        customPlot->setMinimumSize(QSize(0, 0));
        customPlot->setStyleSheet(QString::fromUtf8("background-color: white;border: 0px;"));

        gridLayout_plot->addWidget(customPlot, 1, 1, 1, 1);

        horizontalSlider_trigPre = new QSlider(groupBox_main);
        horizontalSlider_trigPre->setObjectName(QString::fromUtf8("horizontalSlider_trigPre"));
        sizePolicy1.setHeightForWidth(horizontalSlider_trigPre->sizePolicy().hasHeightForWidth());
        horizontalSlider_trigPre->setSizePolicy(sizePolicy1);
        horizontalSlider_trigPre->setMinimumSize(QSize(0, 25));
        horizontalSlider_trigPre->setFont(font1);
        horizontalSlider_trigPre->setStyleSheet(QString::fromUtf8("ctkRangeSlider {\n"
"    min-height: 25px;\n"
"    max-height: 25px;\n"
"	margin-left: 33px;\n"
"	margin-right:2px;\n"
"}\n"
"\n"
"ctkRangeSlider::groove:horizontal {\n"
"    background-color: transparent;\n"
"}\n"
"\n"
"ctkRangeSlider::handle:horizontal {\n"
"     width: 25px;\n"
"	 image: url(:/main/resources/img/range_up.png);\n"
"}\n"
"\n"
"ctkRangeSlider::handle:horizontal:hover {\n"
"     width: 25px;\n"
"	 image: url(:/main/resources/img/range_down2.png);\n"
"}\n"
"\n"
"QSlider {\n"
"    min-height: 25px;\n"
"    max-height: 25px;\n"
"	margin-left: 33px;\n"
"	margin-right:2px;\n"
"}\n"
"\n"
"QSlider::groove:horizontal {\n"
"	background-color: transparent;\n"
"}\n"
"\n"
"QSlider::handle:horizontal {\n"
"     width: 25px;\n"
"	 image: url(:/main/resources/img/range_up.png);\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"	 width: 25px;\n"
"	 image: url(:/main/resources/img/range_up2.png);\n"
"}"));
        horizontalSlider_trigPre->setMaximum(1000);
        horizontalSlider_trigPre->setSingleStep(1);
        horizontalSlider_trigPre->setValue(500);
        horizontalSlider_trigPre->setSliderPosition(500);
        horizontalSlider_trigPre->setOrientation(Qt::Horizontal);
        horizontalSlider_trigPre->setTickPosition(QSlider::NoTicks);
        horizontalSlider_trigPre->setTickInterval(100000);

        gridLayout_plot->addWidget(horizontalSlider_trigPre, 0, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_plot, 1, 0, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setHorizontalSpacing(10);
        gridLayout_3->setVerticalSpacing(0);
        gridLayout_3->setContentsMargins(-1, 0, -1, -1);
        groupBox_ch4_2 = new QGroupBox(groupBox_main);
        groupBox_ch4_2->setObjectName(QString::fromUtf8("groupBox_ch4_2"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(groupBox_ch4_2->sizePolicy().hasHeightForWidth());
        groupBox_ch4_2->setSizePolicy(sizePolicy3);
        groupBox_ch4_2->setMinimumSize(QSize(310, 55));
        groupBox_ch4_2->setMaximumSize(QSize(3000, 10000));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto Medium"));
        font2.setPointSize(11);
        groupBox_ch4_2->setFont(font2);
        groupBox_ch4_2->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 1px solid rgb(150,150,150); border-radius: 5px;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        label_8 = new QLabel(groupBox_ch4_2);
        label_8->setObjectName(QString::fromUtf8("label_8"));
        label_8->setGeometry(QRect(20, 18, 35, 20));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Roboto Light"));
        font3.setPointSize(13);
        font3.setBold(false);
        font3.setWeight(50);
        label_8->setFont(font3);
        textBrowser_measVpp = new QTextBrowser(groupBox_ch4_2);
        textBrowser_measVpp->setObjectName(QString::fromUtf8("textBrowser_measVpp"));
        textBrowser_measVpp->setEnabled(true);
        textBrowser_measVpp->setGeometry(QRect(10, 10, 141, 37));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(textBrowser_measVpp->sizePolicy().hasHeightForWidth());
        textBrowser_measVpp->setSizePolicy(sizePolicy4);
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto Mono Medium"));
        font4.setPointSize(14);
        font4.setBold(false);
        font4.setItalic(false);
        font4.setWeight(50);
        textBrowser_measVpp->setFont(font4);
        textBrowser_measVpp->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_measVpp->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:14pt; font-weight:400;\n"
"	color:black; \n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"    color: gray;\n"
"	background-color: transparent;\n"
"	border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        label_9 = new QLabel(groupBox_ch4_2);
        label_9->setObjectName(QString::fromUtf8("label_9"));
        label_9->setGeometry(QRect(170, 18, 35, 20));
        label_9->setFont(font3);
        textBrowser_measMax = new QTextBrowser(groupBox_ch4_2);
        textBrowser_measMax->setObjectName(QString::fromUtf8("textBrowser_measMax"));
        textBrowser_measMax->setEnabled(true);
        textBrowser_measMax->setGeometry(QRect(460, 10, 141, 37));
        sizePolicy4.setHeightForWidth(textBrowser_measMax->sizePolicy().hasHeightForWidth());
        textBrowser_measMax->setSizePolicy(sizePolicy4);
        textBrowser_measMax->setFont(font4);
        textBrowser_measMax->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_measMax->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:14pt; font-weight:400;\n"
"	color:black; \n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	color:gray;\n"
"	background-color: transparent;\n"
"	border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        textBrowser_measMin = new QTextBrowser(groupBox_ch4_2);
        textBrowser_measMin->setObjectName(QString::fromUtf8("textBrowser_measMin"));
        textBrowser_measMin->setEnabled(true);
        textBrowser_measMin->setGeometry(QRect(310, 10, 141, 37));
        sizePolicy4.setHeightForWidth(textBrowser_measMin->sizePolicy().hasHeightForWidth());
        textBrowser_measMin->setSizePolicy(sizePolicy4);
        textBrowser_measMin->setFont(font4);
        textBrowser_measMin->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_measMin->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:14pt; font-weight:400;\n"
"	color:black; \n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	color:gray;\n"
"	background-color: transparent;\n"
"	border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        textBrowser_measAvg = new QTextBrowser(groupBox_ch4_2);
        textBrowser_measAvg->setObjectName(QString::fromUtf8("textBrowser_measAvg"));
        textBrowser_measAvg->setEnabled(true);
        textBrowser_measAvg->setGeometry(QRect(160, 10, 141, 37));
        sizePolicy4.setHeightForWidth(textBrowser_measAvg->sizePolicy().hasHeightForWidth());
        textBrowser_measAvg->setSizePolicy(sizePolicy4);
        textBrowser_measAvg->setFont(font4);
        textBrowser_measAvg->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_measAvg->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:14pt; font-weight:400;\n"
"	color:black; \n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	color:gray;\n"
"	background-color: transparent;\n"
"	border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        label_11 = new QLabel(groupBox_ch4_2);
        label_11->setObjectName(QString::fromUtf8("label_11"));
        label_11->setGeometry(QRect(320, 18, 35, 20));
        label_11->setFont(font3);
        label_10 = new QLabel(groupBox_ch4_2);
        label_10->setObjectName(QString::fromUtf8("label_10"));
        label_10->setGeometry(QRect(470, 18, 35, 20));
        label_10->setFont(font3);
        textBrowser_measVpp->raise();
        textBrowser_measMax->raise();
        textBrowser_measMin->raise();
        textBrowser_measAvg->raise();
        label_9->raise();
        label_8->raise();
        label_11->raise();
        label_10->raise();

        gridLayout_3->addWidget(groupBox_ch4_2, 1, 0, 1, 1);

        label_meas = new QLabel(groupBox_main);
        label_meas->setObjectName(QString::fromUtf8("label_meas"));
        label_meas->setFont(font2);

        gridLayout_3->addWidget(label_meas, 0, 0, 1, 1);

        label_meas_2 = new QLabel(groupBox_main);
        label_meas_2->setObjectName(QString::fromUtf8("label_meas_2"));
        label_meas_2->setFont(font2);

        gridLayout_3->addWidget(label_meas_2, 0, 1, 1, 1);

        groupBox_ch4_3 = new QGroupBox(groupBox_main);
        groupBox_ch4_3->setObjectName(QString::fromUtf8("groupBox_ch4_3"));
        QSizePolicy sizePolicy5(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy5.setHorizontalStretch(0);
        sizePolicy5.setVerticalStretch(0);
        sizePolicy5.setHeightForWidth(groupBox_ch4_3->sizePolicy().hasHeightForWidth());
        groupBox_ch4_3->setSizePolicy(sizePolicy5);
        groupBox_ch4_3->setMinimumSize(QSize(170, 55));
        groupBox_ch4_3->setMaximumSize(QSize(16777215, 10000));
        groupBox_ch4_3->setFont(font2);
        groupBox_ch4_3->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 1px solid rgb(150,150,150); border-radius: 5px;  }; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        pushButton_cursorsVoff = new QPushButton(groupBox_ch4_3);
        pushButton_cursorsVoff->setObjectName(QString::fromUtf8("pushButton_cursorsVoff"));
        pushButton_cursorsVoff->setGeometry(QRect(10, 10, 71, 36));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Roboto"));
        font5.setPointSize(13);
        pushButton_cursorsVoff->setFont(font5);
        pushButton_cursorsVoff->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Disabled, QIcon::Off);
        pushButton_cursorsVoff->setIcon(icon2);
        pushButton_cursorsVoff->setIconSize(QSize(23, 22));
        pushButton_cursorsVon = new QPushButton(groupBox_ch4_3);
        pushButton_cursorsVon->setObjectName(QString::fromUtf8("pushButton_cursorsVon"));
        pushButton_cursorsVon->setGeometry(QRect(10, 10, 71, 36));
        pushButton_cursorsVon->setFont(font5);
        pushButton_cursorsVon->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/main/resources/img/power-off-gray2.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_cursorsVon->setIcon(icon3);
        pushButton_cursorsVon->setIconSize(QSize(23, 22));
        pushButton_cursorsHoff = new QPushButton(groupBox_ch4_3);
        pushButton_cursorsHoff->setObjectName(QString::fromUtf8("pushButton_cursorsHoff"));
        pushButton_cursorsHoff->setGeometry(QRect(90, 10, 71, 36));
        pushButton_cursorsHoff->setFont(font5);
        pushButton_cursorsHoff->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        pushButton_cursorsHoff->setIcon(icon2);
        pushButton_cursorsHoff->setIconSize(QSize(23, 22));
        pushButton_cursorsHon = new QPushButton(groupBox_ch4_3);
        pushButton_cursorsHon->setObjectName(QString::fromUtf8("pushButton_cursorsHon"));
        pushButton_cursorsHon->setGeometry(QRect(90, 10, 71, 36));
        pushButton_cursorsHon->setFont(font5);
        pushButton_cursorsHon->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        pushButton_cursorsHon->setIcon(icon3);
        pushButton_cursorsHon->setIconSize(QSize(23, 22));

        gridLayout_3->addWidget(groupBox_ch4_3, 1, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout_3, 2, 0, 1, 1);


        verticalLayout->addWidget(groupBox_main);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        groupBox_rightPanel = new QGroupBox(centralwidget);
        groupBox_rightPanel->setObjectName(QString::fromUtf8("groupBox_rightPanel"));
        sizePolicy.setHeightForWidth(groupBox_rightPanel->sizePolicy().hasHeightForWidth());
        groupBox_rightPanel->setSizePolicy(sizePolicy);
        groupBox_rightPanel->setMinimumSize(QSize(388, 0));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Roboto"));
        groupBox_rightPanel->setFont(font6);
        groupBox_rightPanel->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.0em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        verticalLayout_2 = new QVBoxLayout(groupBox_rightPanel);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_ch1 = new QGroupBox(groupBox_rightPanel);
        groupBox_ch1->setObjectName(QString::fromUtf8("groupBox_ch1"));
        groupBox_ch1->setMinimumSize(QSize(390, 100));
        groupBox_ch1->setMaximumSize(QSize(16777215, 150));
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
        QFont font7;
        font7.setFamily(QString::fromUtf8("Roboto Mono Medium"));
        font7.setPointSize(30);
        font7.setBold(true);
        font7.setItalic(false);
        font7.setWeight(62);
        textBrowser_ch1->setFont(font7);
        textBrowser_ch1->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch1->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 2px solid; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"	border-color: #0072BD;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	color:gray;\n"
"	background-color: transparent;\n"
"	border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        doubleSpinBox_gain1 = new QDoubleSpinBox(groupBox_ch1);
        doubleSpinBox_gain1->setObjectName(QString::fromUtf8("doubleSpinBox_gain1"));
        doubleSpinBox_gain1->setEnabled(true);
        doubleSpinBox_gain1->setGeometry(QRect(259, 61, 121, 30));
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
"                                          text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QDoubleSpinBox::up-button:disabled { height:22px"
                        "; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
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
        doubleSpinBox_gain1->setMinimum(-9.900000000000000);
        doubleSpinBox_gain1->setValue(1.000000000000000);
        label_7 = new QLabel(groupBox_ch1);
        label_7->setObjectName(QString::fromUtf8("label_7"));
        label_7->setGeometry(QRect(264, 65, 45, 23));
        label_7->setFont(font3);
        pushButton_disable1 = new QPushButton(groupBox_ch1);
        pushButton_disable1->setObjectName(QString::fromUtf8("pushButton_disable1"));
        pushButton_disable1->setEnabled(true);
        pushButton_disable1->setGeometry(QRect(259, 26, 121, 30));
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        pushButton_disable1->setIcon(icon2);
        pushButton_disable1->setIconSize(QSize(23, 22));
        pushButton_enable1 = new QPushButton(groupBox_ch1);
        pushButton_enable1->setObjectName(QString::fromUtf8("pushButton_enable1"));
        pushButton_enable1->setGeometry(QRect(259, 26, 121, 30));
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        pushButton_enable1->setIcon(icon3);
        pushButton_enable1->setIconSize(QSize(23, 22));
        label_ch1 = new QLabel(groupBox_ch1);
        label_ch1->setObjectName(QString::fromUtf8("label_ch1"));
        label_ch1->setGeometry(QRect(10, 8, 121, 16));
        label_ch1->setFont(font2);
        progressBar_ch1 = new QProgressBar(groupBox_ch1);
        progressBar_ch1->setObjectName(QString::fromUtf8("progressBar_ch1"));
        progressBar_ch1->setEnabled(true);
        progressBar_ch1->setGeometry(QRect(239, 26, 15, 65));
        progressBar_ch1->setStyleSheet(QString::fromUtf8(" QProgressBar {\n"
"     border: 1px solid;\n"
"	 border-color: #0072BD;\n"
"     border-radius: 2px;\n"
"     background-color:  rgb(240,240,240);\n"
" }\n"
"\n"
"QProgressBar::chunk {\n"
"     background-color: #0072BD;\n"
" }\n"
"\n"
"QProgressBar::chunk:disabled {\n"
"	background-color: gray;\n"
" }\n"
"\n"
"QProgressBar:disabled {\n"
"    border-color: gray;\n"
"	background-color:  rgb(210,210,210);\n"
" }"));
        progressBar_ch1->setValue(24);
        progressBar_ch1->setTextVisible(false);
        progressBar_ch1->setOrientation(Qt::Vertical);
        textBrowser_ch1->raise();
        doubleSpinBox_gain1->raise();
        label_7->raise();
        pushButton_enable1->raise();
        pushButton_disable1->raise();
        label_ch1->raise();
        progressBar_ch1->raise();

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
        textBrowser_ch2->setFont(font7);
        textBrowser_ch2->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch2->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 2px solid; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"	border-color: #D95319;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	color:gray;\n"
"	background-color: transparent;\n"
"	border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        doubleSpinBox_gain2 = new QDoubleSpinBox(groupBox_ch2);
        doubleSpinBox_gain2->setObjectName(QString::fromUtf8("doubleSpinBox_gain2"));
        doubleSpinBox_gain2->setEnabled(true);
        doubleSpinBox_gain2->setGeometry(QRect(259, 61, 121, 30));
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
"                                          text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QDoubleSpinBox::up-button:disabled { height:22px"
                        "; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
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
        doubleSpinBox_gain2->setMinimum(-9.900000000000000);
        doubleSpinBox_gain2->setValue(1.000000000000000);
        label_6 = new QLabel(groupBox_ch2);
        label_6->setObjectName(QString::fromUtf8("label_6"));
        label_6->setGeometry(QRect(264, 65, 45, 23));
        label_6->setFont(font3);
        pushButton_disable2 = new QPushButton(groupBox_ch2);
        pushButton_disable2->setObjectName(QString::fromUtf8("pushButton_disable2"));
        pushButton_disable2->setGeometry(QRect(259, 26, 121, 30));
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
"}\n"
"\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        pushButton_disable2->setIcon(icon2);
        pushButton_disable2->setIconSize(QSize(23, 22));
        pushButton_enable2 = new QPushButton(groupBox_ch2);
        pushButton_enable2->setObjectName(QString::fromUtf8("pushButton_enable2"));
        pushButton_enable2->setGeometry(QRect(259, 26, 121, 30));
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        pushButton_enable2->setIcon(icon3);
        pushButton_enable2->setIconSize(QSize(23, 22));
        label_ch2 = new QLabel(groupBox_ch2);
        label_ch2->setObjectName(QString::fromUtf8("label_ch2"));
        label_ch2->setGeometry(QRect(10, 8, 121, 16));
        label_ch2->setFont(font2);
        progressBar_ch2 = new QProgressBar(groupBox_ch2);
        progressBar_ch2->setObjectName(QString::fromUtf8("progressBar_ch2"));
        progressBar_ch2->setEnabled(true);
        progressBar_ch2->setGeometry(QRect(239, 26, 15, 65));
        progressBar_ch2->setStyleSheet(QString::fromUtf8(" QProgressBar {\n"
"     border: 1px solid;\n"
"	 border-color: #D95319;\n"
"     border-radius: 2px;\n"
"     background-color:  rgb(240,240,240);\n"
" }\n"
"\n"
"QProgressBar::chunk {\n"
"     background-color: #D95319;\n"
" }\n"
"\n"
"QProgressBar::chunk:disabled {\n"
"	background-color: gray;\n"
" }\n"
"\n"
"QProgressBar:disabled {\n"
"    border-color: gray;\n"
"	background-color:  rgb(210,210,210);\n"
" }\n"
"\n"
""));
        progressBar_ch2->setValue(50);
        progressBar_ch2->setTextVisible(false);
        progressBar_ch2->setOrientation(Qt::Vertical);
        textBrowser_ch2->raise();
        doubleSpinBox_gain2->raise();
        label_6->raise();
        pushButton_enable2->raise();
        pushButton_disable2->raise();
        label_ch2->raise();
        progressBar_ch2->raise();

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
        textBrowser_ch3->setFont(font7);
        textBrowser_ch3->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch3->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 2px solid; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"	border-color: #77AC30;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	color:gray;\n"
"	background-color: transparent;\n"
"	border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}\n"
""));
        doubleSpinBox_gain3 = new QDoubleSpinBox(groupBox_ch3);
        doubleSpinBox_gain3->setObjectName(QString::fromUtf8("doubleSpinBox_gain3"));
        doubleSpinBox_gain3->setEnabled(true);
        doubleSpinBox_gain3->setGeometry(QRect(259, 61, 121, 30));
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
"                                          text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QDoubleSpinBox::up-button:disabled { height:22px"
                        "; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
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
        doubleSpinBox_gain3->setMinimum(-9.900000000000000);
        doubleSpinBox_gain3->setValue(1.000000000000000);
        label_5 = new QLabel(groupBox_ch3);
        label_5->setObjectName(QString::fromUtf8("label_5"));
        label_5->setGeometry(QRect(264, 65, 45, 23));
        label_5->setFont(font3);
        pushButton_disable3 = new QPushButton(groupBox_ch3);
        pushButton_disable3->setObjectName(QString::fromUtf8("pushButton_disable3"));
        pushButton_disable3->setGeometry(QRect(259, 26, 121, 30));
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        pushButton_disable3->setIcon(icon2);
        pushButton_disable3->setIconSize(QSize(23, 22));
        pushButton_enable3 = new QPushButton(groupBox_ch3);
        pushButton_enable3->setObjectName(QString::fromUtf8("pushButton_enable3"));
        pushButton_enable3->setGeometry(QRect(259, 26, 121, 30));
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        pushButton_enable3->setIcon(icon3);
        pushButton_enable3->setIconSize(QSize(23, 22));
        label_ch3 = new QLabel(groupBox_ch3);
        label_ch3->setObjectName(QString::fromUtf8("label_ch3"));
        label_ch3->setGeometry(QRect(10, 8, 121, 16));
        label_ch3->setFont(font2);
        progressBar_ch3 = new QProgressBar(groupBox_ch3);
        progressBar_ch3->setObjectName(QString::fromUtf8("progressBar_ch3"));
        progressBar_ch3->setGeometry(QRect(239, 26, 15, 65));
        progressBar_ch3->setStyleSheet(QString::fromUtf8(" QProgressBar {\n"
"     border: 1px solid;\n"
"     border-color: #77AC30;\n"
"     border-radius: 2px;\n"
"     background-color:  rgb(240,240,240);\n"
" }\n"
"\n"
"QProgressBar::chunk {\n"
"     background-color: #77AC30;\n"
" }\n"
"\n"
"QProgressBar::chunk:disabled {\n"
"	background-color: gray;\n"
" }\n"
"\n"
"QProgressBar:disabled {\n"
"    border-color: gray;\n"
"	background-color:  rgb(210,210,210);\n"
" }"));
        progressBar_ch3->setValue(75);
        progressBar_ch3->setTextVisible(false);
        progressBar_ch3->setOrientation(Qt::Vertical);
        textBrowser_ch3->raise();
        doubleSpinBox_gain3->raise();
        label_5->raise();
        pushButton_enable3->raise();
        pushButton_disable3->raise();
        label_ch3->raise();
        progressBar_ch3->raise();

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
        textBrowser_ch4->setFont(font7);
        textBrowser_ch4->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch4->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 2px solid; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"	border-color: #7E2F8E;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	color:gray;\n"
"	background-color: transparent;\n"
"	border: 1px solid gray; border-radius:10px;\n"
"	text-align:center;font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:500;\n"
"}"));
        doubleSpinBox_gain4 = new QDoubleSpinBox(groupBox_ch4);
        doubleSpinBox_gain4->setObjectName(QString::fromUtf8("doubleSpinBox_gain4"));
        doubleSpinBox_gain4->setEnabled(true);
        doubleSpinBox_gain4->setGeometry(QRect(259, 61, 121, 30));
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
"                                          text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500; }\n"
"\n"
"QDoubleSpinBox::up-button:disabled { height:22px"
                        "; width: 30px; border: 0px; image: url(:/main/resources/img/arrow_up2.png); }\n"
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
        doubleSpinBox_gain4->setMinimum(-9.900000000000000);
        doubleSpinBox_gain4->setValue(1.000000000000000);
        label_4 = new QLabel(groupBox_ch4);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(264, 65, 45, 23));
        label_4->setFont(font3);
        pushButton_enable4 = new QPushButton(groupBox_ch4);
        pushButton_enable4->setObjectName(QString::fromUtf8("pushButton_enable4"));
        pushButton_enable4->setGeometry(QRect(259, 26, 121, 30));
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        pushButton_enable4->setIcon(icon3);
        pushButton_enable4->setIconSize(QSize(23, 22));
        pushButton_disable4 = new QPushButton(groupBox_ch4);
        pushButton_disable4->setObjectName(QString::fromUtf8("pushButton_disable4"));
        pushButton_disable4->setGeometry(QRect(259, 26, 121, 30));
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
"}\n"
"\n"
"QPushButton:disabled { border: 1px solid rgb(180, 180, 180); color: gray; \n"
"                                       background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #CCCCCC , stop:0.1 #EEEEEE , stop:1 #BBBBBB ); }"));
        pushButton_disable4->setIcon(icon2);
        pushButton_disable4->setIconSize(QSize(23, 22));
        label_ch4 = new QLabel(groupBox_ch4);
        label_ch4->setObjectName(QString::fromUtf8("label_ch4"));
        label_ch4->setGeometry(QRect(10, 8, 121, 16));
        label_ch4->setFont(font2);
        progressBar_ch4 = new QProgressBar(groupBox_ch4);
        progressBar_ch4->setObjectName(QString::fromUtf8("progressBar_ch4"));
        progressBar_ch4->setGeometry(QRect(239, 26, 15, 65));
        progressBar_ch4->setStyleSheet(QString::fromUtf8(" QProgressBar {\n"
"     border: 1px solid;\n"
"     border-color: #7E2F8E;\n"
"     border-radius: 2px;\n"
"     background-color:  rgb(240,240,240);\n"
" }\n"
"\n"
"QProgressBar::chunk {\n"
"     background-color: #7E2F8E;\n"
" }\n"
"\n"
"QProgressBar::chunk:disabled {\n"
"	background-color: gray;\n"
" }\n"
"\n"
"QProgressBar:disabled {\n"
"    border-color: gray;\n"
"	background-color:  rgb(210,210,210);\n"
" }\n"
""));
        progressBar_ch4->setValue(100);
        progressBar_ch4->setTextVisible(false);
        progressBar_ch4->setOrientation(Qt::Vertical);
        progressBar_ch4->setInvertedAppearance(false);
        progressBar_ch4->setTextDirection(QProgressBar::TopToBottom);

        verticalLayout_2->addWidget(groupBox_ch4);

        groupBox_settigns = new QGroupBox(groupBox_rightPanel);
        groupBox_settigns->setObjectName(QString::fromUtf8("groupBox_settigns"));
        QSizePolicy sizePolicy6(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy6.setHorizontalStretch(0);
        sizePolicy6.setVerticalStretch(0);
        sizePolicy6.setHeightForWidth(groupBox_settigns->sizePolicy().hasHeightForWidth());
        groupBox_settigns->setSizePolicy(sizePolicy6);
        groupBox_settigns->setMinimumSize(QSize(0, 140));
        groupBox_settigns->setMaximumSize(QSize(16777215, 140));
        QFont font8;
        font8.setFamily(QString::fromUtf8("Roboto Medium"));
        font8.setPointSize(11);
        font8.setBold(false);
        font8.setItalic(false);
        font8.setWeight(50);
        font8.setKerning(true);
        groupBox_settigns->setFont(font8);
        groupBox_settigns->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 1px solid rgb(150,150,150); border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        label_3 = new QLabel(groupBox_settigns);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(80, 95, 141, 21));
        QFont font9;
        font9.setFamily(QString::fromUtf8("Roboto Light"));
        font9.setPointSize(14);
        font9.setBold(false);
        font9.setWeight(50);
        label_3->setFont(font9);
        dial_display = new QDial(groupBox_settigns);
        dial_display->setObjectName(QString::fromUtf8("dial_display"));
        dial_display->setGeometry(QRect(10, 80, 51, 50));
        dial_display->setMinimum(1);
        dial_display->setMaximum(3000);
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
        spinBox_display->setMaximum(3000);
        spinBox_display->setValue(300);
        label_dial4 = new QLabel(groupBox_settigns);
        label_dial4->setObjectName(QString::fromUtf8("label_dial4"));
        label_dial4->setGeometry(QRect(10, 80, 51, 50));
        label_dial4->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial4->setScaledContents(false);
        spinBox_average = new QSpinBox(groupBox_settigns);
        spinBox_average->setObjectName(QString::fromUtf8("spinBox_average"));
        spinBox_average->setEnabled(true);
        spinBox_average->setGeometry(QRect(70, 35, 231, 41));
        QSizePolicy sizePolicy7(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy7.setHorizontalStretch(0);
        sizePolicy7.setVerticalStretch(0);
        sizePolicy7.setHeightForWidth(spinBox_average->sizePolicy().hasHeightForWidth());
        spinBox_average->setSizePolicy(sizePolicy7);
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
        label_2->setFont(font9);
        label_dial3 = new QLabel(groupBox_settigns);
        label_dial3->setObjectName(QString::fromUtf8("label_dial3"));
        label_dial3->setGeometry(QRect(10, 30, 51, 50));
        label_dial3->setPixmap(QPixmap(QString::fromUtf8(":/main/resources/img/dial1.png")));
        label_dial3->setScaledContents(false);
        pushButton_disable = new QPushButton(groupBox_settigns);
        pushButton_disable->setObjectName(QString::fromUtf8("pushButton_disable"));
        pushButton_disable->setGeometry(QRect(309, 36, 71, 90));
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
        pushButton_enable->setGeometry(QRect(309, 36, 71, 90));
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


        gridLayout->addWidget(groupBox_rightPanel, 0, 3, 1, 1);

        WindowVm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowVm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 1245, 22));
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
        QFont font10;
        font10.setFamily(QString::fromUtf8("Roboto Black"));
        font10.setPointSize(10);
        menuInterpolation->setFont(font10);
        menuMeasure = new QMenu(menubar);
        menuMeasure->setObjectName(QString::fromUtf8("menuMeasure"));
        menuMeasure->setFont(font);
        menuChannel = new QMenu(menuMeasure);
        menuChannel->setObjectName(QString::fromUtf8("menuChannel"));
        menuChannel->setFont(font);
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
        menuMeasure->addAction(actionEnabled);
        menuMeasure->addSeparator();
        menuMeasure->addAction(menuChannel->menuAction());
        menuMeasure->addSeparator();
        menuMeasure->addAction(actionReset);
        menuChannel->addAction(actionChannel_1);
        menuChannel->addAction(actionChannel_2);
        menuChannel->addAction(actionChannel_3);
        menuChannel->addAction(actionChannel_4);

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
        actionSinc->setText(QCoreApplication::translate("WindowVm", "Spline", nullptr));
        actionCSV->setText(QCoreApplication::translate("WindowVm", "CSV", nullptr));
        actionTXT_Tabs->setText(QCoreApplication::translate("WindowVm", "TXT (Tabs)", nullptr));
        actionMAT->setText(QCoreApplication::translate("WindowVm", "MAT", nullptr));
        actionMax->setText(QCoreApplication::translate("WindowVm", "Max", nullptr));
        actionMin->setText(QCoreApplication::translate("WindowVm", "Min", nullptr));
        actionEnabled->setText(QCoreApplication::translate("WindowVm", "Enabled", nullptr));
        actionReset->setText(QCoreApplication::translate("WindowVm", "Reset", nullptr));
        actionChannel_1->setText(QCoreApplication::translate("WindowVm", "Channel 1", nullptr));
        actionChannel_2->setText(QCoreApplication::translate("WindowVm", "Channel 2", nullptr));
        actionChannel_3->setText(QCoreApplication::translate("WindowVm", "Channel 3", nullptr));
        actionChannel_4->setText(QCoreApplication::translate("WindowVm", "Channel 4", nullptr));
        groupBox_main->setTitle(QString());
        groupBox_ch4_2->setTitle(QString());
        label_8->setText(QCoreApplication::translate("WindowVm", "Vpp:", nullptr));
        textBrowser_measVpp->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium','Roboto'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium'; font-weight:496;\">3.1245 </span></p></body></html>", nullptr));
        label_9->setText(QCoreApplication::translate("WindowVm", "Avg:", nullptr));
        textBrowser_measMax->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium','Roboto'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Light'; font-weight:496;\">3.1245 </span></p></body></html>", nullptr));
        textBrowser_measMin->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium','Roboto'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium'; font-weight:496;\">3.1245 </span></p></body></html>", nullptr));
        textBrowser_measAvg->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium','Roboto'; font-size:14pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Light'; font-weight:496;\">3.1245 </span></p></body></html>", nullptr));
        label_11->setText(QCoreApplication::translate("WindowVm", "Min:", nullptr));
        label_10->setText(QCoreApplication::translate("WindowVm", "Max:", nullptr));
        label_meas->setText(QCoreApplication::translate("WindowVm", "Measure (Channel 1)", nullptr));
        label_meas_2->setText(QCoreApplication::translate("WindowVm", "Cursors", nullptr));
        groupBox_ch4_3->setTitle(QString());
        pushButton_cursorsVoff->setText(QCoreApplication::translate("WindowVm", " V", nullptr));
        pushButton_cursorsVon->setText(QCoreApplication::translate("WindowVm", " V", nullptr));
        pushButton_cursorsHoff->setText(QCoreApplication::translate("WindowVm", " H", nullptr));
        pushButton_cursorsHon->setText(QCoreApplication::translate("WindowVm", " H", nullptr));
        groupBox_rightPanel->setTitle(QString());
        groupBox_ch1->setTitle(QString());
        textBrowser_ch1->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.1240 V</span></p></body></html>", nullptr));
        doubleSpinBox_gain1->setPrefix(QString());
        label_7->setText(QCoreApplication::translate("WindowVm", "Scale:", nullptr));
        pushButton_disable1->setText(QString());
        pushButton_enable1->setText(QString());
        label_ch1->setText(QCoreApplication::translate("WindowVm", "Channel 1 (A12)", nullptr));
        groupBox_ch2->setTitle(QString());
        textBrowser_ch2->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.1240 V</span></p></body></html>", nullptr));
        doubleSpinBox_gain2->setPrefix(QString());
        label_6->setText(QCoreApplication::translate("WindowVm", "Scale:", nullptr));
        pushButton_disable2->setText(QString());
        pushButton_enable2->setText(QString());
        label_ch2->setText(QCoreApplication::translate("WindowVm", "Channel 2  (A12)", nullptr));
        groupBox_ch3->setTitle(QString());
        textBrowser_ch3->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.1240 V</span></p></body></html>", nullptr));
        doubleSpinBox_gain3->setPrefix(QString());
        label_5->setText(QCoreApplication::translate("WindowVm", "Scale:", nullptr));
        pushButton_disable3->setText(QString());
        pushButton_enable3->setText(QString());
        label_ch3->setText(QCoreApplication::translate("WindowVm", "Channel 3  (A12)", nullptr));
        groupBox_ch4->setTitle(QString());
        textBrowser_ch4->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:30pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.1240 V</span></p></body></html>", nullptr));
        doubleSpinBox_gain4->setPrefix(QString());
        label_4->setText(QCoreApplication::translate("WindowVm", "Scale:", nullptr));
        pushButton_enable4->setText(QString());
        pushButton_disable4->setText(QString());
        label_ch4->setText(QCoreApplication::translate("WindowVm", "Channel 4  (A12)", nullptr));
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
        menuView->setTitle(QCoreApplication::translate("WindowVm", "Plot", nullptr));
        menuInterpolation->setTitle(QCoreApplication::translate("WindowVm", "Interpolation", nullptr));
        menuMeasure->setTitle(QCoreApplication::translate("WindowVm", "Measure", nullptr));
        menuChannel->setTitle(QCoreApplication::translate("WindowVm", "Channel", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowVm: public Ui_WindowVm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_VM_H
