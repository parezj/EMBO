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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowCntr
{
public:
    QAction *actionAbout;
    QWidget *centralwidget;
    QPushButton *pushButton_enable;
    QTextBrowser *textBrowser_freq;
    QTextBrowser *textBrowser_period;
    QPushButton *pushButton_disable;
    QMenuBar *menubar;
    QMenu *menuHelp;

    void setupUi(QMainWindow *WindowCntr)
    {
        if (WindowCntr->objectName().isEmpty())
            WindowCntr->setObjectName(QString::fromUtf8("WindowCntr"));
        WindowCntr->resize(342, 195);
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
        pushButton_enable->setGeometry(QRect(100, 120, 131, 41));
        QFont font2;
        font2.setPointSize(11);
        pushButton_enable->setFont(font2);
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_enable->setIcon(icon2);
        textBrowser_freq = new QTextBrowser(centralwidget);
        textBrowser_freq->setObjectName(QString::fromUtf8("textBrowser_freq"));
        textBrowser_freq->setGeometry(QRect(50, 20, 251, 31));
        QFont font3;
        font3.setFamily(QString::fromUtf8("Roboto Mono Medium"));
        font3.setBold(false);
        font3.setItalic(false);
        font3.setWeight(50);
        textBrowser_freq->setFont(font3);
        textBrowser_freq->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        textBrowser_period = new QTextBrowser(centralwidget);
        textBrowser_period->setObjectName(QString::fromUtf8("textBrowser_period"));
        textBrowser_period->setGeometry(QRect(50, 70, 251, 31));
        textBrowser_period->setFont(font3);
        textBrowser_period->viewport()->setProperty("cursor", QVariant(QCursor(Qt::IBeamCursor)));
        pushButton_disable = new QPushButton(centralwidget);
        pushButton_disable->setObjectName(QString::fromUtf8("pushButton_disable"));
        pushButton_disable->setGeometry(QRect(100, 120, 131, 41));
        pushButton_disable->setFont(font2);
        QIcon icon3;
        icon3.addFile(QString::fromUtf8(":/main/resources/img/power-off-red.png"), QSize(), QIcon::Normal, QIcon::Off);
        pushButton_disable->setIcon(icon3);
        WindowCntr->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowCntr);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 342, 21));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        WindowCntr->setMenuBar(menubar);

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
        textBrowser_freq->setHtml(QCoreApplication::translate("WindowCntr", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium','Roboto'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Semibold'; font-size:12pt;\">1,5678 MHz</span></p></body></html>", nullptr));
        textBrowser_period->setHtml(QCoreApplication::translate("WindowCntr", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'Roboto Mono Medium','Roboto'; font-size:10pt; font-weight:400; font-style:normal;\">\n"
"<p align=\"right\" style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><span style=\" font-family:'Roboto Mono Bold'; font-size:12pt;\">2,7678 us</span></p></body></html>", nullptr));
        pushButton_disable->setText(QCoreApplication::translate("WindowCntr", " Disable", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("WindowCntr", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowCntr: public Ui_WindowCntr {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_CNTR_H
