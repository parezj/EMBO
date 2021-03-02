/********************************************************************************
** Form generated from reading UI file 'window_pwm.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_PWM_H
#define UI_WINDOW_PWM_H

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

class Ui_WindowPwm
{
public:
    QAction *actionHelp;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuAbout;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowPwm)
    {
        if (WindowPwm->objectName().isEmpty())
            WindowPwm->setObjectName(QString::fromUtf8("WindowPwm"));
        WindowPwm->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        WindowPwm->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowPwm->setWindowIcon(icon);
        actionHelp = new QAction(WindowPwm);
        actionHelp->setObjectName(QString::fromUtf8("actionHelp"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionHelp->setIcon(icon1);
        actionHelp->setFont(font);
        centralwidget = new QWidget(WindowPwm);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        WindowPwm->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowPwm);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuAbout = new QMenu(menubar);
        menuAbout->setObjectName(QString::fromUtf8("menuAbout"));
        WindowPwm->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowPwm);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        WindowPwm->setStatusBar(statusbar);

        menubar->addAction(menuAbout->menuAction());
        menuAbout->addAction(actionHelp);

        retranslateUi(WindowPwm);

        QMetaObject::connectSlotsByName(WindowPwm);
    } // setupUi

    void retranslateUi(QMainWindow *WindowPwm)
    {
        WindowPwm->setWindowTitle(QCoreApplication::translate("WindowPwm", "EMBO - PWM Generator", nullptr));
        actionHelp->setText(QCoreApplication::translate("WindowPwm", "Help", nullptr));
        menuAbout->setTitle(QCoreApplication::translate("WindowPwm", "About", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowPwm: public Ui_WindowPwm {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_PWM_H
