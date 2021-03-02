/********************************************************************************
** Form generated from reading UI file 'window_la.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_LA_H
#define UI_WINDOW_LA_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowLa
{
public:
    QAction *actionHelp;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowLa)
    {
        if (WindowLa->objectName().isEmpty())
            WindowLa->setObjectName(QString::fromUtf8("WindowLa"));
        WindowLa->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        WindowLa->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowLa->setWindowIcon(icon);
        actionHelp = new QAction(WindowLa);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon1);
        actionHelp->setFont(font);
        centralwidget = new QWidget(WindowLa);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        WindowLa->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowLa);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        WindowLa->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowLa);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WindowLa->setStatusBar(statusbar);

        menubar->addAction(menuAbout->menuAction());
        menuAbout->addAction(actionHelp);

        retranslateUi(WindowLa);

        QMetaObject::connectSlotsByName(WindowLa);
    } // setupUi

    void retranslateUi(QMainWindow *WindowLa)
    {
        WindowLa->setWindowTitle(QCoreApplication::translate("WindowLa", "EMBO - Logic Analyzer", nullptr));
        actionHelp->setText(QCoreApplication::translate("WindowLa", "Help", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("WindowLa", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowLa: public Ui_WindowLa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_LA_H
