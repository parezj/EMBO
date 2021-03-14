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
#include <QtWidgets/QApplication>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolButton>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>
#include "__stm32programmer/qcomcheckbox.h"

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QGridLayout *gridLayout_7;
    QVBoxLayout *verticalLayout_3;
    QGroupBox *fileGroup;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *filepath;
    QPushButton *tbBrowse;
    QHBoxLayout *horizontalLayout_2;
    QLabel *hashLabel;
    QComboBox *StartAddress;
    QLabel *label_13;
    QLineEdit *leSize;
    QGroupBox *optionsgroupBox;
    QHBoxLayout *hboxLayout;
    QVBoxLayout *verticalLayout_2;
    QCheckBox *bVerfiy;
    QCheckBox *bSkip;
    QCheckBox *bRun;
    QGridLayout *gridLayout_6;
    QGroupBox *connectgroupBox;
    QGridLayout *gridLayout_4;
    QHBoxLayout *horizontalLayout_8;
    QComboBox *bType;
    QPushButton *ConnectBtn;
    QVBoxLayout *verticalLayout_8;
    QGroupBox *configuregroupBox;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_9;
    QVBoxLayout *verticalLayout_6;
    QLabel *label_4;
    QLabel *label_5;
    QLabel *label_6;
    QLabel *label_7;
    QLabel *label_8;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_19;
    QComCheckBox *bDevice;
    QComboBox *bBaudrate;
    QComboBox *bParity;
    QComboBox *bDatabits;
    QComboBox *bStopbits;
    QComboBox *bFlowControl;
    QGroupBox *devicegroupBox;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_15;
    QLabel *label_12;
    QLabel *lDevice;
    QHBoxLayout *horizontalLayout_16;
    QLabel *label_11;
    QLabel *lType;
    QHBoxLayout *horizontalLayout_17;
    QLabel *label_3;
    QLabel *lDeviceID;
    QHBoxLayout *horizontalLayout_18;
    QLabel *label_10;
    QLabel *lCPU;
    QGroupBox *BtngroupBox;
    QGridLayout *gridLayout_5;
    QPushButton *bWrite;
    QPushButton *bRead;
    QPushButton *bCancel;
    QPushButton *bExit;
    QGroupBox *loggroupBox;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_6;
    QSpacerItem *horizontalSpacer;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label_2;
    QHBoxLayout *horizontalLayout_3;
    QRadioButton *level_1;
    QRadioButton *level_2;
    QRadioButton *level_3;
    QHBoxLayout *horizontalLayout_4;
    QListWidget *loglist;
    QVBoxLayout *verticalLayout_4;
    QToolButton *ClearBtn;
    QToolButton *SaveBtn;
    QGroupBox *progressgroupBox;
    QHBoxLayout *hboxLayout1;
    QHBoxLayout *horizontalLayout_7;
    QProgressBar *progressbar;
    QToolButton *deleteBtn;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(880, 580);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        MainWindow->setMinimumSize(QSize(880, 580));
        MainWindow->setMaximumSize(QSize(880, 580));
        MainWindow->setAcceptDrops(true);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/images/images/Programmer.ico"), QSize(), QIcon::Normal, QIcon::Off);
        MainWindow->setWindowIcon(icon);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 244, 244);"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout_7 = new QGridLayout(centralwidget);
        gridLayout_7->setObjectName(QString::fromUtf8("gridLayout_7"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        fileGroup = new QGroupBox(centralwidget);
        fileGroup->setObjectName(QString::fromUtf8("fileGroup"));
        fileGroup->setMinimumSize(QSize(0, 100));
        fileGroup->setMaximumSize(QSize(16777215, 100));
        fileGroup->setStyleSheet(QString::fromUtf8("background-color:rgb(167,215,231);\n"
""));
        verticalLayout = new QVBoxLayout(fileGroup);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(fileGroup);
        label->setObjectName(QString::fromUtf8("label"));
        label->setMaximumSize(QSize(60, 16777215));

        horizontalLayout->addWidget(label);

        filepath = new QComboBox(fileGroup);
        filepath->setObjectName(QString::fromUtf8("filepath"));
        filepath->setStyleSheet(QString::fromUtf8("background-color:white;\n"
"drop-down: {background-color: rgb(219, 219, 219)};\n"
"\n"
""));
        filepath->setEditable(true);

        horizontalLayout->addWidget(filepath);

        tbBrowse = new QPushButton(fileGroup);
        tbBrowse->setObjectName(QString::fromUtf8("tbBrowse"));
        tbBrowse->setMaximumSize(QSize(80, 16777215));
        tbBrowse->setStyleSheet(QString::fromUtf8("background-color: rgb(3, 96, 233);"));

        horizontalLayout->addWidget(tbBrowse);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        hashLabel = new QLabel(fileGroup);
        hashLabel->setObjectName(QString::fromUtf8("hashLabel"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(hashLabel->sizePolicy().hasHeightForWidth());
        hashLabel->setSizePolicy(sizePolicy1);
        hashLabel->setMaximumSize(QSize(95, 16777215));
        hashLabel->setWordWrap(false);
        hashLabel->setMargin(1);
        hashLabel->setTextInteractionFlags(Qt::LinksAccessibleByMouse|Qt::TextSelectableByMouse);

        horizontalLayout_2->addWidget(hashLabel);

        StartAddress = new QComboBox(fileGroup);
        StartAddress->addItem(QString());
        StartAddress->setObjectName(QString::fromUtf8("StartAddress"));
        StartAddress->setStyleSheet(QString::fromUtf8("background-color:white;\n"
"drop-down: {background-color: rgb(219, 219, 219)};\n"
"\n"
""));
        StartAddress->setEditable(true);

        horizontalLayout_2->addWidget(StartAddress);

        label_13 = new QLabel(fileGroup);
        label_13->setObjectName(QString::fromUtf8("label_13"));
        label_13->setMaximumSize(QSize(30, 16777215));

        horizontalLayout_2->addWidget(label_13);

        leSize = new QLineEdit(fileGroup);
        leSize->setObjectName(QString::fromUtf8("leSize"));
        leSize->setMaximumSize(QSize(80, 16777215));
        leSize->setStyleSheet(QString::fromUtf8("background-color:white;"));

        horizontalLayout_2->addWidget(leSize);


        verticalLayout->addLayout(horizontalLayout_2);


        verticalLayout_3->addWidget(fileGroup);

        optionsgroupBox = new QGroupBox(centralwidget);
        optionsgroupBox->setObjectName(QString::fromUtf8("optionsgroupBox"));
        optionsgroupBox->setMinimumSize(QSize(0, 110));
        optionsgroupBox->setMaximumSize(QSize(16777215, 110));
        optionsgroupBox->setStyleSheet(QString::fromUtf8("background-color:rgb(167,215,231);\n"
""));
        hboxLayout = new QHBoxLayout(optionsgroupBox);
        hboxLayout->setSpacing(0);
        hboxLayout->setObjectName(QString::fromUtf8("hboxLayout"));
        hboxLayout->setContentsMargins(2, 2, 2, 2);
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        bVerfiy = new QCheckBox(optionsgroupBox);
        bVerfiy->setObjectName(QString::fromUtf8("bVerfiy"));
        bVerfiy->setStyleSheet(QString::fromUtf8(""));

        verticalLayout_2->addWidget(bVerfiy);

        bSkip = new QCheckBox(optionsgroupBox);
        bSkip->setObjectName(QString::fromUtf8("bSkip"));

        verticalLayout_2->addWidget(bSkip);

        bRun = new QCheckBox(optionsgroupBox);
        bRun->setObjectName(QString::fromUtf8("bRun"));

        verticalLayout_2->addWidget(bRun);


        hboxLayout->addLayout(verticalLayout_2);


        verticalLayout_3->addWidget(optionsgroupBox);


        gridLayout_7->addLayout(verticalLayout_3, 0, 0, 1, 1);

        gridLayout_6 = new QGridLayout();
        gridLayout_6->setObjectName(QString::fromUtf8("gridLayout_6"));
        connectgroupBox = new QGroupBox(centralwidget);
        connectgroupBox->setObjectName(QString::fromUtf8("connectgroupBox"));
        connectgroupBox->setMinimumSize(QSize(0, 70));
        connectgroupBox->setMaximumSize(QSize(16777215, 70));
        connectgroupBox->setStyleSheet(QString::fromUtf8("background-color:white;"));
        gridLayout_4 = new QGridLayout(connectgroupBox);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        horizontalLayout_8 = new QHBoxLayout();
        horizontalLayout_8->setObjectName(QString::fromUtf8("horizontalLayout_8"));
        bType = new QComboBox(connectgroupBox);
        bType->addItem(QString());
        bType->setObjectName(QString::fromUtf8("bType"));
        bType->setStyleSheet(QString::fromUtf8("background-color:rgb(58,168,219);\n"
"color:white;"));

        horizontalLayout_8->addWidget(bType);

        ConnectBtn = new QPushButton(connectgroupBox);
        ConnectBtn->setObjectName(QString::fromUtf8("ConnectBtn"));
        ConnectBtn->setStyleSheet(QString::fromUtf8("background-color:rgb(186,203,22);\n"
"color:white;"));
        ConnectBtn->setCheckable(true);

        horizontalLayout_8->addWidget(ConnectBtn);


        gridLayout_4->addLayout(horizontalLayout_8, 0, 0, 1, 1);


        gridLayout_6->addWidget(connectgroupBox, 0, 0, 1, 1);

        verticalLayout_8 = new QVBoxLayout();
        verticalLayout_8->setObjectName(QString::fromUtf8("verticalLayout_8"));
        verticalLayout_8->setContentsMargins(-1, 0, -1, -1);
        configuregroupBox = new QGroupBox(centralwidget);
        configuregroupBox->setObjectName(QString::fromUtf8("configuregroupBox"));
        configuregroupBox->setMinimumSize(QSize(0, 230));
        configuregroupBox->setMaximumSize(QSize(16777215, 230));
        configuregroupBox->setStyleSheet(QString::fromUtf8("background-color:rgb(41,59,106);\n"
"color:white;"));
        configuregroupBox->setAlignment(Qt::AlignCenter);
        gridLayout_2 = new QGridLayout(configuregroupBox);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        horizontalLayout_9 = new QHBoxLayout();
        horizontalLayout_9->setObjectName(QString::fromUtf8("horizontalLayout_9"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        label_4 = new QLabel(configuregroupBox);
        label_4->setObjectName(QString::fromUtf8("label_4"));

        verticalLayout_6->addWidget(label_4);

        label_5 = new QLabel(configuregroupBox);
        label_5->setObjectName(QString::fromUtf8("label_5"));

        verticalLayout_6->addWidget(label_5);

        label_6 = new QLabel(configuregroupBox);
        label_6->setObjectName(QString::fromUtf8("label_6"));

        verticalLayout_6->addWidget(label_6);

        label_7 = new QLabel(configuregroupBox);
        label_7->setObjectName(QString::fromUtf8("label_7"));

        verticalLayout_6->addWidget(label_7);

        label_8 = new QLabel(configuregroupBox);
        label_8->setObjectName(QString::fromUtf8("label_8"));

        verticalLayout_6->addWidget(label_8);

        label_9 = new QLabel(configuregroupBox);
        label_9->setObjectName(QString::fromUtf8("label_9"));

        verticalLayout_6->addWidget(label_9);


        horizontalLayout_9->addLayout(verticalLayout_6);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        horizontalLayout_19 = new QHBoxLayout();
        horizontalLayout_19->setSpacing(6);
        horizontalLayout_19->setObjectName(QString::fromUtf8("horizontalLayout_19"));
        horizontalLayout_19->setSizeConstraint(QLayout::SetNoConstraint);
        horizontalLayout_19->setContentsMargins(0, -1, -1, 0);
        bDevice = new QComCheckBox(configuregroupBox);
        bDevice->setObjectName(QString::fromUtf8("bDevice"));
        bDevice->setStyleSheet(QString::fromUtf8("background-color:rgb(229,229,229);\n"
"color:black;"));

        horizontalLayout_19->addWidget(bDevice);


        verticalLayout_5->addLayout(horizontalLayout_19);

        bBaudrate = new QComboBox(configuregroupBox);
        bBaudrate->addItem(QString());
        bBaudrate->addItem(QString());
        bBaudrate->addItem(QString());
        bBaudrate->addItem(QString());
        bBaudrate->addItem(QString());
        bBaudrate->addItem(QString());
        bBaudrate->addItem(QString());
        bBaudrate->addItem(QString());
        bBaudrate->addItem(QString());
        bBaudrate->addItem(QString());
        bBaudrate->setObjectName(QString::fromUtf8("bBaudrate"));
        bBaudrate->setStyleSheet(QString::fromUtf8("background-color:rgb(229,229,229);\n"
"color:black;"));

        verticalLayout_5->addWidget(bBaudrate);

        bParity = new QComboBox(configuregroupBox);
        bParity->addItem(QString());
        bParity->addItem(QString());
        bParity->addItem(QString());
        bParity->setObjectName(QString::fromUtf8("bParity"));
        bParity->setStyleSheet(QString::fromUtf8("background-color:rgb(229,229,229);\n"
"color:black;"));

        verticalLayout_5->addWidget(bParity);

        bDatabits = new QComboBox(configuregroupBox);
        bDatabits->addItem(QString());
        bDatabits->addItem(QString());
        bDatabits->addItem(QString());
        bDatabits->addItem(QString());
        bDatabits->setObjectName(QString::fromUtf8("bDatabits"));
        bDatabits->setEnabled(true);
        bDatabits->setStyleSheet(QString::fromUtf8("background-color:rgb(229,229,229);\n"
"color:black;"));
        bDatabits->setEditable(false);

        verticalLayout_5->addWidget(bDatabits);

        bStopbits = new QComboBox(configuregroupBox);
        bStopbits->addItem(QString());
        bStopbits->addItem(QString());
        bStopbits->setObjectName(QString::fromUtf8("bStopbits"));
        bStopbits->setEnabled(true);
        bStopbits->setStyleSheet(QString::fromUtf8("background-color:rgb(229,229,229);\n"
"color:black;"));

        verticalLayout_5->addWidget(bStopbits);

        bFlowControl = new QComboBox(configuregroupBox);
        bFlowControl->addItem(QString());
        bFlowControl->addItem(QString());
        bFlowControl->addItem(QString());
        bFlowControl->setObjectName(QString::fromUtf8("bFlowControl"));
        bFlowControl->setEnabled(true);
        bFlowControl->setStyleSheet(QString::fromUtf8("background-color:rgb(229,229,229);\n"
"color:black;"));
        bFlowControl->setDuplicatesEnabled(false);

        verticalLayout_5->addWidget(bFlowControl);


        horizontalLayout_9->addLayout(verticalLayout_5);


        gridLayout_2->addLayout(horizontalLayout_9, 0, 0, 1, 1);


        verticalLayout_8->addWidget(configuregroupBox);

        devicegroupBox = new QGroupBox(centralwidget);
        devicegroupBox->setObjectName(QString::fromUtf8("devicegroupBox"));
        devicegroupBox->setMaximumSize(QSize(16777215, 170));
        devicegroupBox->setStyleSheet(QString::fromUtf8("background-color:rgb(41,59,106);\n"
"color:white;"));
        devicegroupBox->setAlignment(Qt::AlignCenter);
        gridLayout_3 = new QGridLayout(devicegroupBox);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        horizontalLayout_15 = new QHBoxLayout();
        horizontalLayout_15->setObjectName(QString::fromUtf8("horizontalLayout_15"));
        label_12 = new QLabel(devicegroupBox);
        label_12->setObjectName(QString::fromUtf8("label_12"));

        horizontalLayout_15->addWidget(label_12);

        lDevice = new QLabel(devicegroupBox);
        lDevice->setObjectName(QString::fromUtf8("lDevice"));
        lDevice->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_15->addWidget(lDevice);


        verticalLayout_7->addLayout(horizontalLayout_15);

        horizontalLayout_16 = new QHBoxLayout();
        horizontalLayout_16->setObjectName(QString::fromUtf8("horizontalLayout_16"));
        label_11 = new QLabel(devicegroupBox);
        label_11->setObjectName(QString::fromUtf8("label_11"));

        horizontalLayout_16->addWidget(label_11);

        lType = new QLabel(devicegroupBox);
        lType->setObjectName(QString::fromUtf8("lType"));
        lType->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_16->addWidget(lType);


        verticalLayout_7->addLayout(horizontalLayout_16);

        horizontalLayout_17 = new QHBoxLayout();
        horizontalLayout_17->setObjectName(QString::fromUtf8("horizontalLayout_17"));
        label_3 = new QLabel(devicegroupBox);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        horizontalLayout_17->addWidget(label_3);

        lDeviceID = new QLabel(devicegroupBox);
        lDeviceID->setObjectName(QString::fromUtf8("lDeviceID"));
        lDeviceID->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_17->addWidget(lDeviceID);


        verticalLayout_7->addLayout(horizontalLayout_17);

        horizontalLayout_18 = new QHBoxLayout();
        horizontalLayout_18->setObjectName(QString::fromUtf8("horizontalLayout_18"));
        label_10 = new QLabel(devicegroupBox);
        label_10->setObjectName(QString::fromUtf8("label_10"));

        horizontalLayout_18->addWidget(label_10);

        lCPU = new QLabel(devicegroupBox);
        lCPU->setObjectName(QString::fromUtf8("lCPU"));
        lCPU->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout_18->addWidget(lCPU);


        verticalLayout_7->addLayout(horizontalLayout_18);


        gridLayout_3->addLayout(verticalLayout_7, 0, 0, 1, 1);


        verticalLayout_8->addWidget(devicegroupBox);


        gridLayout_6->addLayout(verticalLayout_8, 1, 0, 1, 1);


        gridLayout_7->addLayout(gridLayout_6, 0, 1, 4, 1);

        BtngroupBox = new QGroupBox(centralwidget);
        BtngroupBox->setObjectName(QString::fromUtf8("BtngroupBox"));
        BtngroupBox->setMaximumSize(QSize(16777215, 70));
        BtngroupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 244, 244);"));
        gridLayout_5 = new QGridLayout(BtngroupBox);
        gridLayout_5->setObjectName(QString::fromUtf8("gridLayout_5"));
        bWrite = new QPushButton(BtngroupBox);
        bWrite->setObjectName(QString::fromUtf8("bWrite"));

        gridLayout_5->addWidget(bWrite, 0, 3, 1, 1);

        bRead = new QPushButton(BtngroupBox);
        bRead->setObjectName(QString::fromUtf8("bRead"));

        gridLayout_5->addWidget(bRead, 0, 2, 1, 1);

        bCancel = new QPushButton(BtngroupBox);
        bCancel->setObjectName(QString::fromUtf8("bCancel"));
        bCancel->setEnabled(false);

        gridLayout_5->addWidget(bCancel, 0, 1, 1, 1);

        bExit = new QPushButton(BtngroupBox);
        bExit->setObjectName(QString::fromUtf8("bExit"));

        gridLayout_5->addWidget(bExit, 0, 4, 1, 1);


        gridLayout_7->addWidget(BtngroupBox, 1, 0, 1, 1);

        loggroupBox = new QGroupBox(centralwidget);
        loggroupBox->setObjectName(QString::fromUtf8("loggroupBox"));
        loggroupBox->setMaximumSize(QSize(16777215, 160));
        loggroupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 244, 244);"));
        gridLayout = new QGridLayout(loggroupBox);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_6->addItem(horizontalSpacer);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label_2 = new QLabel(loggroupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        horizontalLayout_5->addWidget(label_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        level_1 = new QRadioButton(loggroupBox);
        level_1->setObjectName(QString::fromUtf8("level_1"));
        level_1->setChecked(true);

        horizontalLayout_3->addWidget(level_1);

        level_2 = new QRadioButton(loggroupBox);
        level_2->setObjectName(QString::fromUtf8("level_2"));

        horizontalLayout_3->addWidget(level_2);

        level_3 = new QRadioButton(loggroupBox);
        level_3->setObjectName(QString::fromUtf8("level_3"));

        horizontalLayout_3->addWidget(level_3);


        horizontalLayout_5->addLayout(horizontalLayout_3);


        horizontalLayout_6->addLayout(horizontalLayout_5);


        gridLayout->addLayout(horizontalLayout_6, 0, 0, 1, 1);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        loglist = new QListWidget(loggroupBox);
        loglist->setObjectName(QString::fromUtf8("loglist"));
        loglist->setStyleSheet(QString::fromUtf8("background-color: white;"));

        horizontalLayout_4->addWidget(loglist);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        ClearBtn = new QToolButton(loggroupBox);
        ClearBtn->setObjectName(QString::fromUtf8("ClearBtn"));
        ClearBtn->setStyleSheet(QString::fromUtf8("background: transparent;   \n"
"border:none"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/images/images/clear.png"), QSize(), QIcon::Normal, QIcon::Off);
        ClearBtn->setIcon(icon1);

        verticalLayout_4->addWidget(ClearBtn);

        SaveBtn = new QToolButton(loggroupBox);
        SaveBtn->setObjectName(QString::fromUtf8("SaveBtn"));
        SaveBtn->setStyleSheet(QString::fromUtf8("background: transparent;   \n"
"border:none"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/images/images/save.png"), QSize(), QIcon::Normal, QIcon::Off);
        SaveBtn->setIcon(icon2);

        verticalLayout_4->addWidget(SaveBtn);


        horizontalLayout_4->addLayout(verticalLayout_4);


        gridLayout->addLayout(horizontalLayout_4, 1, 0, 1, 1);


        gridLayout_7->addWidget(loggroupBox, 2, 0, 1, 1);

        progressgroupBox = new QGroupBox(centralwidget);
        progressgroupBox->setObjectName(QString::fromUtf8("progressgroupBox"));
        progressgroupBox->setMaximumSize(QSize(16777215, 70));
        progressgroupBox->setStyleSheet(QString::fromUtf8("background-color: rgb(244, 244, 244);"));
        hboxLayout1 = new QHBoxLayout(progressgroupBox);
        hboxLayout1->setSpacing(2);
        hboxLayout1->setObjectName(QString::fromUtf8("hboxLayout1"));
        hboxLayout1->setContentsMargins(2, 2, 2, 2);
        horizontalLayout_7 = new QHBoxLayout();
        horizontalLayout_7->setObjectName(QString::fromUtf8("horizontalLayout_7"));
        progressbar = new QProgressBar(progressgroupBox);
        progressbar->setObjectName(QString::fromUtf8("progressbar"));
        progressbar->setStyleSheet(QString::fromUtf8("background-color: white;"));
        progressbar->setValue(0);
        progressbar->setTextVisible(true);

        horizontalLayout_7->addWidget(progressbar);

        deleteBtn = new QToolButton(progressgroupBox);
        deleteBtn->setObjectName(QString::fromUtf8("deleteBtn"));
        deleteBtn->setStyleSheet(QString::fromUtf8("background: transparent;   \n"
"border:none"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/images/images/delete.png"), QSize(), QIcon::Normal, QIcon::Off);
        deleteBtn->setIcon(icon3);

        horizontalLayout_7->addWidget(deleteBtn);


        hboxLayout1->addLayout(horizontalLayout_7);


        gridLayout_7->addWidget(progressgroupBox, 3, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(bExit, SIGNAL(clicked()), MainWindow, SLOT(close()));

        bBaudrate->setCurrentIndex(9);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "STM32 Programmer by Yang", nullptr));
        fileGroup->setTitle(QCoreApplication::translate("MainWindow", "File programming", nullptr));
        label->setText(QCoreApplication::translate("MainWindow", "File path:", nullptr));
        tbBrowse->setText(QCoreApplication::translate("MainWindow", "Browse", nullptr));
        hashLabel->setText(QCoreApplication::translate("MainWindow", "start Address", nullptr));
        StartAddress->setItemText(0, QCoreApplication::translate("MainWindow", "0x08000000", nullptr));

        label_13->setText(QCoreApplication::translate("MainWindow", "Size", nullptr));
        optionsgroupBox->setTitle(QCoreApplication::translate("MainWindow", " Programming options:", nullptr));
        bVerfiy->setText(QCoreApplication::translate("MainWindow", "Verify programming", nullptr));
        bSkip->setText(QCoreApplication::translate("MainWindow", "Skip flash erase before programming", nullptr));
        bRun->setText(QCoreApplication::translate("MainWindow", "Run after programming", nullptr));
        connectgroupBox->setTitle(QString());
        bType->setItemText(0, QCoreApplication::translate("MainWindow", "UART", nullptr));

#if QT_CONFIG(tooltip)
        ConnectBtn->setToolTip(QCoreApplication::translate("MainWindow", "Connect to Device", nullptr));
#endif // QT_CONFIG(tooltip)
#if QT_CONFIG(statustip)
        ConnectBtn->setStatusTip(QCoreApplication::translate("MainWindow", "connect to device", nullptr));
#endif // QT_CONFIG(statustip)
        ConnectBtn->setText(QCoreApplication::translate("MainWindow", "Connect", nullptr));
        configuregroupBox->setTitle(QCoreApplication::translate("MainWindow", "UART configure", nullptr));
        label_4->setText(QCoreApplication::translate("MainWindow", "Port", nullptr));
        label_5->setText(QCoreApplication::translate("MainWindow", "Baudrate", nullptr));
        label_6->setText(QCoreApplication::translate("MainWindow", "Parity", nullptr));
        label_7->setText(QCoreApplication::translate("MainWindow", "Data bits", nullptr));
        label_8->setText(QCoreApplication::translate("MainWindow", "Stop bits", nullptr));
        label_9->setText(QCoreApplication::translate("MainWindow", "Flow control", nullptr));
        bBaudrate->setItemText(0, QCoreApplication::translate("MainWindow", "1200", nullptr));
        bBaudrate->setItemText(1, QCoreApplication::translate("MainWindow", "2400", nullptr));
        bBaudrate->setItemText(2, QCoreApplication::translate("MainWindow", "4800", nullptr));
        bBaudrate->setItemText(3, QCoreApplication::translate("MainWindow", "9600", nullptr));
        bBaudrate->setItemText(4, QCoreApplication::translate("MainWindow", "14400", nullptr));
        bBaudrate->setItemText(5, QCoreApplication::translate("MainWindow", "19200", nullptr));
        bBaudrate->setItemText(6, QCoreApplication::translate("MainWindow", "38400", nullptr));
        bBaudrate->setItemText(7, QCoreApplication::translate("MainWindow", "56000", nullptr));
        bBaudrate->setItemText(8, QCoreApplication::translate("MainWindow", "57600", nullptr));
        bBaudrate->setItemText(9, QCoreApplication::translate("MainWindow", "115200", nullptr));

        bParity->setItemText(0, QCoreApplication::translate("MainWindow", "Even", nullptr));
        bParity->setItemText(1, QCoreApplication::translate("MainWindow", "Odd", nullptr));
        bParity->setItemText(2, QCoreApplication::translate("MainWindow", "None", nullptr));

        bDatabits->setItemText(0, QCoreApplication::translate("MainWindow", "8", nullptr));
        bDatabits->setItemText(1, QCoreApplication::translate("MainWindow", "7", nullptr));
        bDatabits->setItemText(2, QCoreApplication::translate("MainWindow", "6", nullptr));
        bDatabits->setItemText(3, QCoreApplication::translate("MainWindow", "5", nullptr));

        bStopbits->setItemText(0, QCoreApplication::translate("MainWindow", "1", nullptr));
        bStopbits->setItemText(1, QCoreApplication::translate("MainWindow", "2", nullptr));

        bFlowControl->setItemText(0, QCoreApplication::translate("MainWindow", "Off", nullptr));
        bFlowControl->setItemText(1, QCoreApplication::translate("MainWindow", "RTC/CTS", nullptr));
        bFlowControl->setItemText(2, QCoreApplication::translate("MainWindow", "XON/XOFF", nullptr));

        devicegroupBox->setTitle(QCoreApplication::translate("MainWindow", "Device information", nullptr));
        label_12->setText(QCoreApplication::translate("MainWindow", "Device", nullptr));
        lDevice->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_11->setText(QCoreApplication::translate("MainWindow", "Type", nullptr));
        lType->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_3->setText(QCoreApplication::translate("MainWindow", "Device ID", nullptr));
        lDeviceID->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        label_10->setText(QCoreApplication::translate("MainWindow", "CPU", nullptr));
        lCPU->setText(QCoreApplication::translate("MainWindow", "-", nullptr));
        BtngroupBox->setTitle(QString());
#if QT_CONFIG(statustip)
        bWrite->setStatusTip(QCoreApplication::translate("MainWindow", "Write data from 'Binary File' to 'Device'", nullptr));
#endif // QT_CONFIG(statustip)
        bWrite->setText(QCoreApplication::translate("MainWindow", "Write", nullptr));
#if QT_CONFIG(statustip)
        bRead->setStatusTip(QCoreApplication::translate("MainWindow", "Read data from 'Device' to 'Binary File'", nullptr));
#endif // QT_CONFIG(statustip)
        bRead->setText(QCoreApplication::translate("MainWindow", "Read", nullptr));
#if QT_CONFIG(statustip)
        bCancel->setStatusTip(QCoreApplication::translate("MainWindow", "Cancel current process.", nullptr));
#endif // QT_CONFIG(statustip)
        bCancel->setText(QCoreApplication::translate("MainWindow", "Cancel", nullptr));
#if QT_CONFIG(statustip)
        bExit->setStatusTip(QCoreApplication::translate("MainWindow", "Exit  BootLoader", nullptr));
#endif // QT_CONFIG(statustip)
        bExit->setText(QCoreApplication::translate("MainWindow", "Exit", nullptr));
        loggroupBox->setTitle(QCoreApplication::translate("MainWindow", "Log", nullptr));
        label_2->setText(QCoreApplication::translate("MainWindow", "Verbosity level", nullptr));
        level_1->setText(QCoreApplication::translate("MainWindow", "1", nullptr));
        level_2->setText(QCoreApplication::translate("MainWindow", "2", nullptr));
        level_3->setText(QCoreApplication::translate("MainWindow", "3", nullptr));
#if QT_CONFIG(statustip)
        ClearBtn->setStatusTip(QCoreApplication::translate("MainWindow", "clean log", nullptr));
#endif // QT_CONFIG(statustip)
        ClearBtn->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
#if QT_CONFIG(statustip)
        SaveBtn->setStatusTip(QCoreApplication::translate("MainWindow", "save log to file", nullptr));
#endif // QT_CONFIG(statustip)
        SaveBtn->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
        progressgroupBox->setTitle(QString());
        progressbar->setFormat(QCoreApplication::translate("MainWindow", "%p%", nullptr));
        deleteBtn->setText(QCoreApplication::translate("MainWindow", "...", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
