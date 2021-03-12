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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_WindowScope
{
public:
    QAction *actionAbout;
    QWidget *centralwidget;
    QGridLayout *gridLayout;
    QPushButton *pushButton_ch1disable;
    QMenuBar *menubar;
    QMenu *menuHelp;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *WindowScope)
    {
        if (WindowScope->objectName().isEmpty())
            WindowScope->setObjectName(QString::fromUtf8("WindowScope"));
        WindowScope->resize(410, 299);
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
        pushButton_ch1disable = new QPushButton(centralwidget);
        pushButton_ch1disable->setObjectName(QString::fromUtf8("pushButton_ch1disable"));
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(pushButton_ch1disable->sizePolicy().hasHeightForWidth());
        pushButton_ch1disable->setSizePolicy(sizePolicy);
        QFont font1;
        font1.setFamily(QString::fromUtf8("Roboto"));
        font1.setPointSize(13);
        font1.setBold(false);
        font1.setWeight(50);
        font1.setKerning(true);
        pushButton_ch1disable->setFont(font1);
        pushButton_ch1disable->setStyleSheet(QString::fromUtf8("QPushButton {    \n"
"    padding: 0.2em 0.2em 0.3em 0.2em;\n"
"    border: 1px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
"    background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B);\n"
"    color: black;\n"
"}\n"
"\n"
"QPushButton:hover:!pressed\n"
"{\n"
"	border: 1px solid rgb(150, 150, 150);;\n"
"	border-radius: 5px;\n"
" 	background: #FFFFFF;\n"
"	color:#2f836a;\n"
"}\n"
"\n"
"QPushButton:pressed\n"
"{\n"
"	border: 2px solid rgb(150, 150, 150);\n"
"	border-radius: 5px;\n"
" 	background: #AAAAAA;\n"
"	color:white;\n"
"}"));
        QIcon icon2;
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Normal, QIcon::Off);
        icon2.addFile(QString::fromUtf8(":/main/resources/img/power-off-green3.png"), QSize(), QIcon::Disabled, QIcon::Off);
        pushButton_ch1disable->setIcon(icon2);
        pushButton_ch1disable->setIconSize(QSize(23, 22));

        gridLayout->addWidget(pushButton_ch1disable, 0, 0, 1, 1);

        WindowScope->setCentralWidget(centralwidget);
        menubar = new QMenuBar(WindowScope);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 410, 21));
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
        pushButton_ch1disable->setText(QString());
        menuHelp->setTitle(QCoreApplication::translate("WindowScope", "Help", nullptr));
    } // retranslateUi

};

namespace Ui {
    class WindowScope: public Ui_WindowScope {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_WINDOW_SCOPE_H
