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
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QSlider>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowLa
{
public:
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QSlider *horizontalSlider_freq;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowLa)
    {
        if (WindowLa->objectName().isEmpty())
            WindowLa->setObjectName(QString::fromUtf8("WindowLa"));
        WindowLa->resize(417, 245);
        QFont font;
        font.setFamily(QString::fromUtf8("Roboto"));
        font.setPointSize(10);
        WindowLa->setFont(font);
        QIcon icon;
        icon.addFile(QString::fromUtf8(":/main/resources/img/icon.png"), QSize(), QIcon::Normal, QIcon::Off);
        WindowLa->setWindowIcon(icon);
        actionAbout = new QAction(WindowLa);
        actionAbout->setObjectName(QString::fromUtf8("actionAbout"));
        QIcon icon1;
        icon1.addFile(QString::fromUtf8(":/main/resources/img/info.svg"), QSize(), QIcon::Normal, QIcon::Off);
        actionAbout->setIcon(icon1);
        actionAbout->setFont(font);
        centralwidget = new QWidget(WindowLa);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        gridLayout = new QGridLayout(centralwidget);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        horizontalSlider_freq = new QSlider(centralwidget);
        horizontalSlider_freq->setObjectName(QString::fromUtf8("horizontalSlider_freq"));
        QSizePolicy sizePolicy(QSizePolicy::Expanding, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(horizontalSlider_freq->sizePolicy().hasHeightForWidth());
        horizontalSlider_freq->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setBold(false);
        font1.setWeight(50);
        horizontalSlider_freq->setFont(font1);
        horizontalSlider_freq->setStyleSheet(QString::fromUtf8("QSlider::handle:horizontal {\n"
"    background-color: #449f84;\n"
"    border: 1px solid;\n"
"}\n"
"\n"
"QSlider::handle:horizontal:hover {\n"
"    background-color: #51bf9f;\n"
"    border: 1px solid;\n"
"}"));
        horizontalSlider_freq->setMaximum(5000000);
        horizontalSlider_freq->setValue(50);
        horizontalSlider_freq->setOrientation(Qt::Horizontal);
        horizontalSlider_freq->setTickPosition(QSlider::TicksBelow);
        horizontalSlider_freq->setTickInterval(100000);

        gridLayout->addWidget(horizontalSlider_freq, 0, 0, 1, 1);

        WindowLa->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowLa);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 417, 21));
        menuHelp = new QMenu(menubar);
        menuHelp->setObjectName(QString::fromUtf8("menuHelp"));
        WindowLa->setMenuBar(menubar);
        statusbar = new QStatusBar(WindowLa);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        statusbar->setStyleSheet(QString::fromUtf8("background-color: rgb(230, 230, 230);"));
        WindowLa->setStatusBar(statusbar);

        menubar->addAction(menuHelp->menuAction());
        menuHelp->addAction(actionAbout);

        retranslateUi(WindowLa);

        QMetaObject::connectSlotsByName(WindowLa);
    } // setupUi

    void retranslateUi(QMainWindow *WindowLa)
    {
        WindowLa->setWindowTitle(QCoreApplication::translate("WindowLa", "EMBO - Logic Analyzer", nullptr));
        actionAbout->setText(QCoreApplication::translate("WindowLa", "About", nullptr));
        menuHelp->setTitle(QCoreApplication::translate("WindowLa", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowLa: public Ui_WindowLa {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_LA_H
