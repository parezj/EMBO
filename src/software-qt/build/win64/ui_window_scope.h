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
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowScope
{
public:
    QAction *actionHelp;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowScope)
    {
        if (WindowScope->objectName().isEmpty())
            WindowScope->setObjectName(QString::fromUtf8("WindowScope"));
        WindowScope->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        WindowScope->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowScope->setWindowIcon(icon);
        actionHelp = new QAction(WindowScope);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon1);
        actionHelp->setFont(font);
        centralwidget = new QWidget(WindowScope);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        WindowScope->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowScope);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        WindowScope->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowScope);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WindowScope->setStatusBar(statusbar);

        menubar->addAction(menuAbout->menuAction());
        menuAbout->addAction(actionHelp);

        retranslateUi(WindowScope);

        QMetaObject::connectSlotsByName(WindowScope);
    } // setupUi

    void retranslateUi(QMainWindow *WindowScope)
    {
        WindowScope->setWindowTitle(QCoreApplication::translate("WindowScope", "EMBO - Oscilloscope", nullptr));
        actionHelp->setText(QCoreApplication::translate("WindowScope", "Help", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("WindowScope", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowScope: public Ui_WindowScope {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_SCOPE_H
