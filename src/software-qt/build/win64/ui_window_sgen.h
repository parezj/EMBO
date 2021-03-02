/********************************************************************************
** Form generated from reading UI file 'window_sgen.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_SGEN_H
#define UI_WINDOW_SGEN_H

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

class Ui_WindowSgen
{
public:
    QAction *actionAbout;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowSgen)
    {
        if (WindowSgen->objectName().isEmpty())
            WindowSgen->setObjectName(QString::fromUtf8("WindowSgen"));
        WindowSgen->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        WindowSgen->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowSgen->setWindowIcon(icon);
        actionAbout = new QAction(WindowSgen);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon1);
        actionAbout->setFont(font);
        centralwidget = new QWidget(WindowSgen);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        WindowSgen->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowSgen);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        menuHelp->setFont(font);
        WindowSgen->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowSgen);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WindowSgen->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(WindowSgen);

        QMetaObject::connectSlotsByName(WindowSgen);
    } // setupUi

    void retranslateUi(QMainWindow *WindowSgen)
    {
        WindowSgen->setWindowTitle(QCoreApplication::translate("WindowSgen", "EMBO - Signal Generator", nullptr));
        actionAbout->setText(QCoreApplication::translate("WindowSgen", "About", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("WindowSgen", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowSgen: public Ui_WindowSgen {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_SGEN_H
