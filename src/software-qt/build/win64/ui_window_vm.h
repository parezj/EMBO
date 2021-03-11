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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSpacerItem>
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
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QGroupBox *groupBox_rightPanel;
    QVBoxLayout *verticalLayout_2;
    QGroupBox *groupBox_ch1;
    QVBoxLayout *verticalLayout_3;
    QSpacerItem *verticalSpacer_2;
    QTextBrowser *textBrowser_ch1;
    QGroupBox *groupBox_ch2;
    QVBoxLayout *verticalLayout_5;
    QSpacerItem *verticalSpacer_5;
    QTextBrowser *textBrowser_ch2;
    QGroupBox *groupBox_ch3;
    QVBoxLayout *verticalLayout_4;
    QSpacerItem *verticalSpacer_3;
    QTextBrowser *textBrowser_ch3;
    QGroupBox *groupBox_ch4;
    QVBoxLayout *verticalLayout;
    QSpacerItem *verticalSpacer;
    QTextBrowser *textBrowser_ch4;
    QSpacerItem *verticalSpacer_4;
    QCustomPlot *customPlot;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowVm)
    {
        if (WindowVm->objectName().isEmpty())
            WindowVm->setObjectName(QString::fromUtf8("WindowVm"));
        WindowVm->resize(901, 757);
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
        groupBox_rightPanel->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        verticalLayout_2 = new QVBoxLayout(groupBox_rightPanel);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        groupBox_ch1 = new QGroupBox(groupBox_rightPanel);
        groupBox_ch1->setObjectName(QString::fromUtf8("groupBox_ch1"));
        groupBox_ch1->setMinimumSize(QSize(0, 120));
        groupBox_ch1->setMaximumSize(QSize(16777215, 150));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto Medium"));
        font2.setPointSize(11);
        groupBox_ch1->setFont(font2);
        groupBox_ch1->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        verticalLayout_3 = new QVBoxLayout(groupBox_ch1);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalSpacer_2 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_3->addItem(verticalSpacer_2);

        textBrowser_ch1 = new QTextBrowser(groupBox_ch1);
        textBrowser_ch1->setObjectName(QString::fromUtf8("textBrowser_ch1"));
        textBrowser_ch1->setEnabled(true);
        sizePolicy.setHeightForWidth(textBrowser_ch1->sizePolicy().hasHeightForWidth());
        textBrowser_ch1->setSizePolicy(sizePolicy);
        textBrowser_ch1->setMaximumSize(QSize(16777215, 80));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Roboto Mono Medium"));
        font3.setPointSize(40);
        font3.setBold(true);
        font3.setItalic(false);
        font3.setWeight(62);
        textBrowser_ch1->setFont(font3);
        textBrowser_ch1->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch1->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: transparent;\n"
"	border-color: transparent; border-width: 1px solid gray; border-style:inset; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:500;\n"
"}"));

        verticalLayout_3->addWidget(textBrowser_ch1);


        verticalLayout_2->addWidget(groupBox_ch1);

        groupBox_ch2 = new QGroupBox(groupBox_rightPanel);
        groupBox_ch2->setObjectName(QString::fromUtf8("groupBox_ch2"));
        groupBox_ch2->setMinimumSize(QSize(0, 120));
        groupBox_ch2->setMaximumSize(QSize(16777215, 150));
        groupBox_ch2->setFont(font2);
        groupBox_ch2->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        verticalLayout_5 = new QVBoxLayout(groupBox_ch2);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        verticalSpacer_5 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_5->addItem(verticalSpacer_5);

        textBrowser_ch2 = new QTextBrowser(groupBox_ch2);
        textBrowser_ch2->setObjectName(QString::fromUtf8("textBrowser_ch2"));
        textBrowser_ch2->setEnabled(true);
        sizePolicy.setHeightForWidth(textBrowser_ch2->sizePolicy().hasHeightForWidth());
        textBrowser_ch2->setSizePolicy(sizePolicy);
        textBrowser_ch2->setMinimumSize(QSize(300, 0));
        textBrowser_ch2->setMaximumSize(QSize(16777215, 80));
        textBrowser_ch2->setFont(font3);
        textBrowser_ch2->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch2->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: transparent;\n"
"	border-color: transparent; border-width: 1px solid gray; border-style:inset; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:500;\n"
"}"));

        verticalLayout_5->addWidget(textBrowser_ch2);


        verticalLayout_2->addWidget(groupBox_ch2);

        groupBox_ch3 = new QGroupBox(groupBox_rightPanel);
        groupBox_ch3->setObjectName(QString::fromUtf8("groupBox_ch3"));
        groupBox_ch3->setMinimumSize(QSize(0, 120));
        groupBox_ch3->setMaximumSize(QSize(16777215, 150));
        groupBox_ch3->setFont(font2);
        groupBox_ch3->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        verticalLayout_4 = new QVBoxLayout(groupBox_ch3);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        verticalSpacer_3 = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout_4->addItem(verticalSpacer_3);

        textBrowser_ch3 = new QTextBrowser(groupBox_ch3);
        textBrowser_ch3->setObjectName(QString::fromUtf8("textBrowser_ch3"));
        textBrowser_ch3->setEnabled(true);
        sizePolicy.setHeightForWidth(textBrowser_ch3->sizePolicy().hasHeightForWidth());
        textBrowser_ch3->setSizePolicy(sizePolicy);
        textBrowser_ch3->setMaximumSize(QSize(16777215, 80));
        textBrowser_ch3->setFont(font3);
        textBrowser_ch3->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch3->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: transparent;\n"
"	border-color: transparent; border-width: 1px solid gray; border-style:inset; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:500;\n"
"}"));

        verticalLayout_4->addWidget(textBrowser_ch3);


        verticalLayout_2->addWidget(groupBox_ch3);

        groupBox_ch4 = new QGroupBox(groupBox_rightPanel);
        groupBox_ch4->setObjectName(QString::fromUtf8("groupBox_ch4"));
        groupBox_ch4->setMinimumSize(QSize(0, 120));
        groupBox_ch4->setMaximumSize(QSize(16777215, 150));
        groupBox_ch4->setFont(font2);
        groupBox_ch4->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(200,200,200);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        verticalLayout = new QVBoxLayout(groupBox_ch4);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalSpacer = new QSpacerItem(20, 10, QSizePolicy::Minimum, QSizePolicy::Preferred);

        verticalLayout->addItem(verticalSpacer);

        textBrowser_ch4 = new QTextBrowser(groupBox_ch4);
        textBrowser_ch4->setObjectName(QString::fromUtf8("textBrowser_ch4"));
        textBrowser_ch4->setEnabled(true);
        sizePolicy.setHeightForWidth(textBrowser_ch4->sizePolicy().hasHeightForWidth());
        textBrowser_ch4->setSizePolicy(sizePolicy);
        textBrowser_ch4->setMaximumSize(QSize(16777215, 80));
        textBrowser_ch4->setFont(font3);
        textBrowser_ch4->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_ch4->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: transparent;\n"
"	border-color: transparent; border-width: 1px solid gray; border-style:inset; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:500;\n"
"}"));

        verticalLayout->addWidget(textBrowser_ch4);


        verticalLayout_2->addWidget(groupBox_ch4);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_4);


        gridLayout->addWidget(groupBox_rightPanel, 0, 2, 1, 1);

        customPlot = new QCustomPlot(centralwidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setEnabled(true);
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy1);

        gridLayout->addWidget(customPlot, 0, 1, 1, 1);

        WindowVm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowVm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 901, 21));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        WindowVm->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowVm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        WindowVm->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(WindowVm);

        QMetaObject::connectSlotsByName(WindowVm);
    } // setupUi

    void retranslateUi(QMainWindow *WindowVm)
    {
        WindowVm->setWindowTitle(QCoreApplication::translate("WindowVm", "EMBO - Voltmeter", nullptr));
        actionAbout->setText(QCoreApplication::translate("WindowVm", "About", nullptr));
        groupBox_rightPanel->setTitle(QString());
        groupBox_ch1->setTitle(QCoreApplication::translate("WindowVm", "Channel 1", nullptr));
        textBrowser_ch1->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.124 V</span></p></body></html>", nullptr));
        groupBox_ch2->setTitle(QCoreApplication::translate("WindowVm", "Channel 2", nullptr));
        textBrowser_ch2->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.124 V</span></p></body></html>", nullptr));
        groupBox_ch3->setTitle(QCoreApplication::translate("WindowVm", "Channel 3", nullptr));
        textBrowser_ch3->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.124 V</span></p></body></html>", nullptr));
        groupBox_ch4->setTitle(QCoreApplication::translate("WindowVm", "Channel 4", nullptr));
        textBrowser_ch4->setHtml(QCoreApplication::translate("WindowVm", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:40pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"center\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">3.124 V</span></p></body></html>", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("WindowVm", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowVm: public Ui_WindowVm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_VM_H
