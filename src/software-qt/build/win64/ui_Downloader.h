/********************************************************************************
** Form generated from reading UI file 'Downloader.ui'
**
** Created by: Qt User Interface Compiler version 5.14.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DOWNLOADER_H
#define UI_DOWNLOADER_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Downloader
{
public:
    QVBoxLayout *verticalLayout;
    QWidget *widget;
    QHBoxLayout *horizontalLayout;
    QLabel *updater_icon;
    QWidget *progressFrame;
    QVBoxLayout *verticalLayout_2;
    QLabel *downloadLabel;
    QProgressBar *progressBar;
    QLabel *timeLabel;
    QWidget *buttonFrame;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *buttonSpacer;
    QPushButton *openButton;
    QPushButton *stopButton;

    void setupUi(QWidget *Downloader)
    {
        if (Downloader->objectName().isEmpty())
            Downloader->setObjectName(QString::fromUtf8("Downloader"));
        Downloader->setWindowModality(Qt::ApplicationModal);
        Downloader->resize(464, 168);
        QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(Downloader->sizePolicy().hasHeightForWidth());
        Downloader->setSizePolicy(sizePolicy);
        verticalLayout = new QVBoxLayout(Downloader);
        verticalLayout->setSpacing(0);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        verticalLayout->setContentsMargins(12, 12, 12, 12);
        widget = new QWidget(Downloader);
        widget->setObjectName(QString::fromUtf8("widget"));
        horizontalLayout = new QHBoxLayout(widget);
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalLayout->setContentsMargins(0, 0, 0, 0);
        updater_icon = new QLabel(widget);
        updater_icon->setObjectName(QString::fromUtf8("updater_icon"));
        updater_icon->setMinimumSize(QSize(96, 96));
        updater_icon->setPixmap(QPixmap(QString::fromUtf8(":/icons/update.png")));

        horizontalLayout->addWidget(updater_icon);

        progressFrame = new QWidget(widget);
        progressFrame->setObjectName(QString::fromUtf8("progressFrame"));
        verticalLayout_2 = new QVBoxLayout(progressFrame);
        verticalLayout_2->setSpacing(0);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        downloadLabel = new QLabel(progressFrame);
        downloadLabel->setObjectName(QString::fromUtf8("downloadLabel"));
        QFont font;
        font.setBold(true);
        font.setWeight(75);
        downloadLabel->setFont(font);

        verticalLayout_2->addWidget(downloadLabel);

        progressBar = new QProgressBar(progressFrame);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setMinimumSize(QSize(320, 0));
        progressBar->setValue(0);
        progressBar->setInvertedAppearance(false);

        verticalLayout_2->addWidget(progressBar);

        timeLabel = new QLabel(progressFrame);
        timeLabel->setObjectName(QString::fromUtf8("timeLabel"));

        verticalLayout_2->addWidget(timeLabel);


        horizontalLayout->addWidget(progressFrame);


        verticalLayout->addWidget(widget);

        buttonFrame = new QWidget(Downloader);
        buttonFrame->setObjectName(QString::fromUtf8("buttonFrame"));
        horizontalLayout_2 = new QHBoxLayout(buttonFrame);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalLayout_2->setContentsMargins(12, 12, 12, 12);
        buttonSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(buttonSpacer);

        openButton = new QPushButton(buttonFrame);
        openButton->setObjectName(QString::fromUtf8("openButton"));

        horizontalLayout_2->addWidget(openButton);

        stopButton = new QPushButton(buttonFrame);
        stopButton->setObjectName(QString::fromUtf8("stopButton"));

        horizontalLayout_2->addWidget(stopButton);


        verticalLayout->addWidget(buttonFrame);


        retranslateUi(Downloader);

        QMetaObject::connectSlotsByName(Downloader);
    } // setupUi

    void retranslateUi(QWidget *Downloader)
    {
        Downloader->setWindowTitle(QCoreApplication::translate("Downloader", "Updater", nullptr));
        updater_icon->setText(QString());
        downloadLabel->setText(QCoreApplication::translate("Downloader", "Downloading updates", nullptr));
        timeLabel->setText(QCoreApplication::translate("Downloader", "Time remaining: 0 minutes", nullptr));
        openButton->setText(QCoreApplication::translate("Downloader", "Open", nullptr));
        stopButton->setText(QCoreApplication::translate("Downloader", "Stop", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Downloader: public Ui_Downloader {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DOWNLOADER_H
