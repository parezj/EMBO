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
#include <QtWidgets/QRadioButton>
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
    QGroupBox *groupBox_4;
    QRadioButton *radioButton_fast;
    QRadioButton *radioButton_precise;
    QLabel *label_3;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowCntr)
    {
        if (WindowCntr->objectName().isEmpty())
            WindowCntr->setObjectName(QString::fromUtf8("WindowCntr"));
        WindowCntr->setWindowModality(Qt::NonModal);
        WindowCntr->resize(341, 289);
        QSizePolicy sizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(WindowCntr->sizePolicy().hasHeightForWidth());
        WindowCntr->setSizePolicy(sizePolicy);
        WindowCntr->setMinimumSize(QSize(341, 289));
        WindowCntr->setMaximumSize(QSize(341, 289));
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
        pushButton_enable->setGeometry(QRect(95, 186, 151, 41));
        QFont font2;
        font2.setFamily(QString::fromUtf8("Roboto"));
        font2.setPointSize(13);
        pushButton_enable->setFont(font2);
        pushButton_enable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2,\n"
"                                  stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"	text-align:left;\n"
"	padding-left:13px;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color: #29715c;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"	color:#2f836a;\n"
" 	background: #FFFFFF;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-gray2.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-gray2.png"), QSize(), QIcon::Disabled, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-gray2.png"), QSize(), QIcon::Disabled, QIcon::On);
        pushButton_enable->setIcon(icon2);
        pushButton_enable->setIconSize(QSize(22, 22));
        pushButton_disable = new QPushButton(centralwidget);
        pushButton_disable->setObjectName(QString::fromUtf8("pushButton_disable"));
        pushButton_disable->setEnabled(true);
        pushButton_disable->setGeometry(QRect(95, 186, 151, 41));
        pushButton_disable->setFont(font2);
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
"	color:#2f836a;\n"
" 	background: #FFFFFF;\n"
"}\n"
"\n"
"QPushButton { \n"
"	text-align:left;\n"
"	padding-left:13px;\n"
"}"));
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon3.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Disabled, QIcon::Off);
        pushButton_disable->setIcon(icon3);
        pushButton_disable->setIconSize(QSize(23, 22));
        line = new QFrame(centralwidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setGeometry(QRect(0, 234, 401, 20));
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
        label_2->setGeometry(QRect(20, 80, 91, 21));
        QFont font4;
        font4.setFamily(QString::fromUtf8("Roboto Light"));
        font4.setPointSize(14);
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
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:16pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: transparent;\n"
"	border-color: transparent; border-width: 1px solid gray; border-style:inset; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:16pt; font-weight:500;\n"
"}"));
        label = new QLabel(groupBox_3);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(20, 30, 101, 21));
        label->setFont(font4);
        textBrowser_freq = new QTextBrowser(groupBox_3);
        textBrowser_freq->setObjectName(QString::fromUtf8("textBrowser_freq"));
        textBrowser_freq->setEnabled(true);
        textBrowser_freq->setGeometry(QRect(10, 20, 301, 41));
        textBrowser_freq->setFont(font5);
        textBrowser_freq->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_freq->setStyleSheet(QString::fromUtf8("QTextBrowser {\n"
"	background-color: rgba(240,240,240, 1.0);border: 1px solid gray; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:16pt; font-weight:500;\n"
"}\n"
"\n"
"QTextBrowser:disabled {\n"
"	background-color: transparent;\n"
"	border-color: transparent; border-width: 1px solid gray; border-style:inset; border-radius:10px;\n"
"	text-align:right;font-family:'Roboto Mono Medium'; font-size:16pt; font-weight:500;\n"
"}"));
        textBrowser_period->raise();
        textBrowser_freq->raise();
        label->raise();
        label_2->raise();
        groupBox_4 = new QGroupBox(centralwidget);
        groupBox_4->setObjectName(QString::fromUtf8("groupBox_4"));
        groupBox_4->setGeometry(QRect(10, 125, 321, 45));
        sizePolicy1.setHeightForWidth(groupBox_4->sizePolicy().hasHeightForWidth());
        groupBox_4->setSizePolicy(sizePolicy1);
        groupBox_4->setFont(font3);
        groupBox_4->setStyleSheet(QString::fromUtf8("QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px;  margin-top: 0.5em;}; \n"
"QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"));
        radioButton_fast = new QRadioButton(groupBox_4);
        radioButton_fast->setObjectName(QString::fromUtf8("radioButton_fast"));
        radioButton_fast->setGeometry(QRect(210, 16, 101, 21));
        QFont font6;
        font6.setFamily(QString::fromUtf8("Roboto"));
        font6.setPointSize(14);
        radioButton_fast->setFont(font6);
        radioButton_fast->setStyleSheet(QString::fromUtf8("QRadioButton:checked {\n"
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
        radioButton_fast->setIconSize(QSize(20, 20));
        radioButton_fast->setChecked(false);
        radioButton_fast->setAutoExclusive(false);
        radioButton_precise = new QRadioButton(groupBox_4);
        radioButton_precise->setObjectName(QString::fromUtf8("radioButton_precise"));
        radioButton_precise->setGeometry(QRect(100, 16, 101, 21));
        radioButton_precise->setFont(font6);
        radioButton_precise->setStyleSheet(QString::fromUtf8("QRadioButton:checked {\n"
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
        radioButton_precise->setIconSize(QSize(20, 20));
        radioButton_precise->setChecked(true);
        radioButton_precise->setAutoExclusive(false);
        label_3 = new QLabel(groupBox_4);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(20, 16, 61, 21));
        label_3->setFont(font4);
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
        pushButton_enable->setText(QCoreApplication::translate("WindowCntr", " Counter OFF", nullptr));
        pushButton_disable->setText(QCoreApplication::translate("WindowCntr", " Counter ON", nullptr));
        groupBox_3->setTitle(QString());
        label_2->setText(QCoreApplication::translate("WindowCntr", "Period:", nullptr));
        textBrowser_period->setMarkdown(QCoreApplication::translate("WindowCntr", "**545.4456 ns**\n"
"\n"
"", nullptr));
        textBrowser_period->setHtml(QCoreApplication::translate("WindowCntr", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:16pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto';\">545.4456 ns</span></p></body></html>", nullptr));
        label->setText(QCoreApplication::translate("WindowCntr", "Frequency:", nullptr));
        textBrowser_freq->setHtml(QCoreApplication::translate("WindowCntr", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium'; font-size:16pt; font-weight:496; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Medium','Roboto Mono Medium';\">545.4456 MHz</span></p></body></html>", nullptr));
        groupBox_4->setTitle(QString());
        radioButton_fast->setText(QCoreApplication::translate("WindowCntr", "Fast", nullptr));
        radioButton_precise->setText(QCoreApplication::translate("WindowCntr", "Precise", nullptr));
        label_3->setText(QCoreApplication::translate("WindowCntr", "Mode:", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("WindowCntr", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowCntr: public Ui_WindowCntr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_CNTR_H
