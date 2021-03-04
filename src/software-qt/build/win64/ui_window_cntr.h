/********************************************************************************
** Form generated from reading UI file 'window_cntr.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_CNTR_H
#define UI_WINDOW_CNTR_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QFrame>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowCntr
{
public:
    QAction *actionAbout;
    QWidget *centralwidget;
    QPushButton *pushButton_enable;
    QPushButton *pushButton_disable;
    QFrame *line;
    QGroupBox *groupBox_3;
    QLabel *label_2;
    QTextBrowser *textBrowser_period;
    QLabel *label;
    QTextBrowser *textBrowser_freq;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowCntr)
    {
        if (WindowCntr->objectName().isEmpty())
            WindowCntr->setObjectName(QString::fromUtf8("WindowCntr"));
        WindowCntr->setWindowModality(Qt::NonModal);
        WindowCntr->resize(341, 245);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WindowCntr->sizePolicy().hasHeightForWidth());
        WindowCntr->setSizePolicy(sizePolicy);
        WindowCntr->setMinimumSize(QSize(341, 245));
        WindowCntr->setMaximumSize(QSize(341, 246));
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        WindowCntr->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowCntr->setWindowIcon(icon);
        actionAbout = new QAction(WindowCntr);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon1);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(10);
        font1.setItalic(false);
        actionAbout->setFont(font1);
        centralwidget = new QWidget(WindowCntr);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        pushButton_enable = new QPushButton(centralwidget);
        pushButton_enable->setObjectName(QString::fromUtf8("pushButton_enable"));
        pushButton_enable->setGeometry(QRect(105, 140, 131, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto"));
        font2.setPointSize(14);
        pushButton_enable->setFont(font2);
        pushButton_enable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
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
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_enable->setIcon(icon2);
        pushButton_enable->setIconSize(QSize(18, 18));
        pushButton_disable = new QPushButton(centralwidget);
        pushButton_disable->setObjectName(QString::fromUtf8("pushButton_disable"));
        pushButton_disable->setGeometry(QRect(105, 140, 131, 41));
        pushButton_disable->setFont(font2);
        pushButton_disable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
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
        icon3.addFile(QString::fromUtf8(":/main/resources/img/power-off-red.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_disable->setIcon(icon3);
        pushButton_disable->setIconSize(QSize(18, 18));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 190, 401, 20));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);
        groupBox_3 = new QGroupBox(centralwidget);
        groupBox_3->setObjectName(QString::fromUtf8("groupBox_3"));
        groupBox_3->setGeometry(QRect(10, 1, 321, 121));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(groupBox_3->sizePolicy().hasHeightForWidth());
        groupBox_3->setSizePolicy(sizePolicy1);
        QFont font3;
        font3.setFamily(QString::fromUtf8("Roboto"));
        font3.setPointSize(10);
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        font3.setKerning(true);
        groupBox_3->setFont(font3);
        groupBox_3->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        label_2 = new QLabel(groupBox_3);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(20, 80, 111, 21));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto Thin"));
        font4.setPointSize(16);
        font4.setBold(false);
        font4.setWeight(50);
        label_2->setFont(font4);
        textBrowser_period = new QTextBrowser(groupBox_3);
        textBrowser_period->setObjectName(QString::fromUtf8("textBrowser_period"));
        textBrowser_period->setGeometry(QRect(10, 70, 301, 41));
        QFont font5;
        font5.setFamily(QString::fromUtf8("Roboto Mono Medium"));
        font5.setPointSize(16);
        font5.setBold(true);
        font5.setItalic(false);
        font5.setWeight(62);
        textBrowser_period->setFont(font5);
        textBrowser_period->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_period->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: rgba(240,240,240, 1.0);\n"
"	border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;\n"
"}"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 111, 21));
        label->setFont(font4);
        textBrowser_freq = new QTextBrowser(groupBox_3);
        textBrowser_freq->setObjectName(QString::fromUtf8("textBrowser_freq"));
        textBrowser_freq->setEnabled(true);
        textBrowser_freq->setGeometry(QRect(10, 20, 301, 41));
        textBrowser_freq->setFont(font5);
        textBrowser_freq->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_freq->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(255,255,255, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: rgba(240,240,240, 1.0);\n"
"	border-color: transparent; border-width: 1px; border-style:inset; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:500;\n"
"}"));
        textBrowser_period->raise();
        textBrowser_freq->raise();
        label->raise();
        label_2->raise();
        WindowCntr->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowCntr);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 341, 21));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        WindowCntr->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowCntr);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        WindowCntr->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(WindowCntr);

        QMetaObject::connectSlotsByName(WindowCntr);
    } // setupUi

    void retranslateUi(QMainWindow *WindowCntr)
    {
        WindowCntr->setWindowTitle(QCoreApplication::translate("WindowCntr", "EMBO - Counter", nullptr));
        actionAbout->setText(QCoreApplication::translate("WindowCntr", "About", nullptr));
        pushButton_enable->setText(QCoreApplication::translate("WindowCntr", " Enable", nullptr));
        pushButton_disable->setText(QCoreApplication::translate("WindowCntr", " Disable", nullptr));
        groupBox_3->setTitle(QString());
        label_2->setText(QCoreApplication::translate("WindowCntr", "Period:", nullptr));
        textBrowser_period->setMarkdown(QCoreApplication::translate("WindowCntr", "`545.4456 ns`\n"
"\n"
"", nullptr));
        textBrowser_period->setHtml(QCoreApplication::translate("WindowCntr", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">545.4456 ns</p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("WindowCntr", "Frequency:", nullptr));
        textBrowser_freq->setHtml(QCoreApplication::translate("WindowCntr", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium','Roboto'; font-size:16pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">545.4456 MHz</p></body></html>", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("WindowCntr", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowCntr: public Ui_WindowCntr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_CNTR_H
