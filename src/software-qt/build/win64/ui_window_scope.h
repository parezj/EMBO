/********************************************************************************
** Form generated from reading UI file 'window_scope.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_SCOPE_H
#define UI_WINDOW_SCOPE_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>
#include "lib/qcustomplot.h"

QT_BEGIN_NAMESPACE

class Ui_WindowScope
{
public:
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QCustomPlot *customPlot;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowScope)
    {
        if (WindowScope->objectName().isEmpty())
            WindowScope->setObjectName(QString::fromUtf8("WindowScope"));
        WindowScope->resize(462, 324);
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        WindowScope->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowScope->setWindowIcon(icon);
        actionAbout = new QAction(WindowScope);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon1);
        actionAbout->setFont(font);
        centralwidget = new QWidget(WindowScope);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        customPlot = new QCustomPlot(centralwidget);
        customPlot->setObjectName(QString::fromUtf8("customPlot"));

        gridLayout->addWidget(customPlot, 0, 0, 1, 1);

        WindowScope->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowScope);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 462, 22));
        menubar->setFont(font);
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        WindowScope->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowScope);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        WindowScope->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(WindowScope);

        QMetaObject::connectSlotsByName(WindowScope);
    } // setupUi

    void retranslateUi(QMainWindow *WindowScope)
    {
        WindowScope->setWindowTitle(QCoreApplication::translate("WindowScope", "EMBO - Oscilloscope", nullptr));
        actionAbout->setText(QCoreApplication::translate("WindowScope", "About", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("WindowScope", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowScope: public Ui_WindowScope {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_SCOPE_H
