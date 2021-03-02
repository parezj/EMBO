/********************************************************************************
** Form generated from reading UI file 'window_counter.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_WINDOW_COUNTER_H
#define UI_WINDOW_COUNTER_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_window_counter
{
public:
    QAction *actionAbout;
    QWidget *centralwidget;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *window_counter)
    {
        if (window_counter->objectName().isEmpty())
            window_counter->setObjectName(QString::fromUtf8("window_counter"));
        window_counter->resize(800, 600);
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        window_counter->setFont(font);
        actionAbout = new QAction(window_counter);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(10);
        font1.setItalic(false);
        actionAbout->setFont(font1);
        centralwidget = new QWidget(window_counter);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        window_counter->setCentralWidget(centralwidget);
        menubar = new QMenuBar(window_counter);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 800, 21));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        window_counter->setMenuBar(menubar);
        statusbar = new QStatusBar(window_counter);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        window_counter->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(window_counter);

        QMetaObject::connectSlotsByName(window_counter);
    } // setupUi

    void retranslateUi(QMainWindow *window_counter)
    {
        window_counter->setWindowTitle(QCoreApplication::translate("window_counter", "MainWindow", nullptr));
        actionAbout->setText(QCoreApplication::translate("window_counter", "About", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("window_counter", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class window_counter: public Ui_window_counter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_COUNTER_H
