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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
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
    QPushButton *pushButton_3;
    QPushButton *pushButton_7;
    QPushButton *pushButton_6;
    QPushButton *pushButton_5;
    QPushButton *pushButton_4;
    QCustomPlot *customPlot;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowVm)
    {
        if (WindowVm->objectName().isEmpty())
            WindowVm->setObjectName(QString::fromUtf8("WindowVm"));
        WindowVm->resize(844, 546);
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
        pushButton_3 = new QPushButton(groupBox_rightPanel);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(pushButton_3->sizePolicy().hasHeightForWidth());
        pushButton_3->setSizePolicy(sizePolicy1);
        pushButton_3->setMinimumSize(QSize(100, 40));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto"));
        font2.setPointSize(13);
        pushButton_3->setFont(font2);
        pushButton_3->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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

        verticalLayout_2->addWidget(pushButton_3);

        pushButton_7 = new QPushButton(groupBox_rightPanel);
        pushButton_7->setObjectName(QString::fromUtf8("pushButton_7"));
        sizePolicy1.setHeightForWidth(pushButton_7->sizePolicy().hasHeightForWidth());
        pushButton_7->setSizePolicy(sizePolicy1);
        pushButton_7->setMinimumSize(QSize(100, 40));
        pushButton_7->setFont(font2);
        pushButton_7->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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

        verticalLayout_2->addWidget(pushButton_7);

        pushButton_6 = new QPushButton(groupBox_rightPanel);
        pushButton_6->setObjectName(QString::fromUtf8("pushButton_6"));
        sizePolicy1.setHeightForWidth(pushButton_6->sizePolicy().hasHeightForWidth());
        pushButton_6->setSizePolicy(sizePolicy1);
        pushButton_6->setMinimumSize(QSize(100, 40));
        pushButton_6->setFont(font2);
        pushButton_6->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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

        verticalLayout_2->addWidget(pushButton_6);

        pushButton_5 = new QPushButton(groupBox_rightPanel);
        pushButton_5->setObjectName(QString::fromUtf8("pushButton_5"));
        sizePolicy1.setHeightForWidth(pushButton_5->sizePolicy().hasHeightForWidth());
        pushButton_5->setSizePolicy(sizePolicy1);
        pushButton_5->setMinimumSize(QSize(100, 40));
        pushButton_5->setFont(font2);
        pushButton_5->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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

        verticalLayout_2->addWidget(pushButton_5);

        pushButton_4 = new QPushButton(groupBox_rightPanel);
        pushButton_4->setObjectName(QString::fromUtf8("pushButton_4"));
        sizePolicy1.setHeightForWidth(pushButton_4->sizePolicy().hasHeightForWidth());
        pushButton_4->setSizePolicy(sizePolicy1);
        pushButton_4->setMinimumSize(QSize(100, 40));
        pushButton_4->setFont(font2);
        pushButton_4->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
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

        verticalLayout_2->addWidget(pushButton_4);


        gridLayout->addWidget(groupBox_rightPanel, 0, 2, 1, 1);

        customPlot = new QCustomPlot(centralwidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));
        customPlot->setEnabled(true);
        QSizePolicy sizePolicy2(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(customPlot->sizePolicy().hasHeightForWidth());
        customPlot->setSizePolicy(sizePolicy2);

        gridLayout->addWidget(customPlot, 0, 1, 1, 1);

        WindowVm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowVm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 844, 21));
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
        pushButton_3->setText(QCoreApplication::translate("WindowVm", "Button 1", nullptr));
        pushButton_7->setText(QCoreApplication::translate("WindowVm", "Button 2", nullptr));
        pushButton_6->setText(QCoreApplication::translate("WindowVm", "Button 3", nullptr));
        pushButton_5->setText(QCoreApplication::translate("WindowVm", "Button 4", nullptr));
        pushButton_4->setText(QCoreApplication::translate("WindowVm", "Button 5", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("WindowVm", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowVm: public Ui_WindowVm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_VM_H
