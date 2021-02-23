#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>
#include <QLabel>
#include <QGridLayout>
#include <QStatusBar>
#include <QMessageBox>
#include <QListView>
#include <QFontDatabase>
#include <QtSerialPort/QSerialPortInfo>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent),
      m_ui(new Ui::MainWindow),
      m_serial(new QSerialPort(this))
{
    m_ui->setupUi(this);

    m_ui->pushButton_Disconnect->hide();
    m_ui->groupBox_scope->hide();
    m_ui->groupBox_la->hide();
    m_ui->groupBox_vm->hide();
    m_ui->groupBox_pwm->hide();
    m_ui->groupBox_sgen->hide();
    m_ui->groupBox_cntr->hide();

    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Display-Bold.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Display-Light.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Display-Medium.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Display-Regular.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Display-Semibold.ttf");

    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Text-Bold.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Text-Light.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Text-Medium.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Text-Regular.ttf");
    QFontDatabase::addApplicationFont(":/resources/fonts/SF-UI-Text-Semibold.ttf");

    QFont font("SF-UI-Display");
    font.setStyleHint(QFont::Monospace);
    QApplication::setFont(font);

    QWidget* widget = new QWidget();
    QFont font1( "SF-UI-Display", 10, QFont::Normal);
    m_status_icon = new QLabel(this);
    QLabel* status_txt = new QLabel(" Disconnected");
    QLabel* status_author = new QLabel("CTU FEE - Jakub Pařez 2021 ");

    m_plug_on = QPixmap(":/resources/img/plug_on.png");
    m_plug_off = QPixmap(":/resources/img/plug_off.png");
    m_status_icon->setPixmap(m_plug_off);
    m_status_icon->setFixedWidth(15);
    m_status_icon->setFixedHeight(18);
    m_status_icon->setScaledContents(true);

    status_txt->setObjectName("status_txt");
    status_author->setObjectName("status_author");
    status_txt->setFont(font1);
    status_author->setFont(font1);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(m_status_icon,0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(status_txt,0,1,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->addWidget(status_author,0,2,1,1,Qt::AlignVCenter | Qt::AlignRight);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);

    QString style1 = "QGroupBox {background-color: rgb(248,248,248);border: 1px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \
                      QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}";
    m_ui->groupBox_scope->setStyleSheet(style1);
    m_ui->groupBox_la->setStyleSheet(style1);
    m_ui->groupBox_vm->setStyleSheet(style1);
    m_ui->groupBox_pwm->setStyleSheet(style1);
    m_ui->groupBox_sgen->setStyleSheet(style1);
    m_ui->groupBox_cntr->setStyleSheet(style1);

    QString style2 = "QGroupBox {background-color: rgb(220,220,220);border: 0px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \
                      QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}";

    m_ui->groupBox_device->setStyleSheet(style2);
    m_ui->groupBox_instr1->setStyleSheet(style2);
    m_ui->groupBox_instr2->setStyleSheet(style2);
    m_ui->groupBox_ports->setStyleSheet(style2);

    connect(m_serial, &QSerialPort::errorOccurred, this, &MainWindow::on_serial_errorOccurred);
    connect(m_serial, &QSerialPort::readyRead, this, &MainWindow::on_serial_readyRead);

    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        m_ui->listWidget_ports->addItem(port.portName());
    }
    if (m_ui->listWidget_ports->children().count() > 0)
    {
        m_ui->listWidget_ports->setCurrentRow(0);
        m_ui->pushButton_Connect->setEnabled(true);
    }
}

MainWindow::~MainWindow()
{
    delete m_ui;
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msg;
    msg.setText("About");
    msg.exec();
}

void MainWindow::on_actionOpen_triggered()
{
    QMessageBox msg;
    msg.setText("Open");
    msg.exec();
}

void MainWindow::on_pushButton_Scan_clicked()
{
    m_ui->listWidget_ports->clear();
    Q_FOREACH(QSerialPortInfo port, QSerialPortInfo::availablePorts()) {
        m_ui->listWidget_ports->addItem(port.portName());
    }
    if (m_ui->listWidget_ports->children().count() > 0)
        m_ui->listWidget_ports->setCurrentRow(0);
    m_ui->pushButton_Connect->setEnabled(m_ui->listWidget_ports->children().count() > 0);
}

void MainWindow::on_pushButton_Connect_clicked()
{
    m_ui->pushButton_Connect->setText("Connecting");
    m_ui->pushButton_Connect->setEnabled(false);
    QModelIndex selIdx = m_ui->listWidget_ports->currentIndex();
    QString selPort = selIdx.data().toString();

    m_serial->setPortName(selPort);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    if (m_serial->open(QIODevice::ReadWrite))
    {
        m_ui->pushButton_Connect->hide();
        m_ui->pushButton_Disconnect->show();

        QLabel *status_txt = m_ui->statusbar->findChild<QLabel*>("status_txt");
        status_txt->setText(" Connected (" + selPort + ")");
        m_status_icon->setPixmap(m_plug_on);

        m_ui->listWidget_ports->setEnabled(false);
        m_ui->pushButton_Scan->setEnabled(false);
        m_ui->groupBox_scope->show();
        m_ui->groupBox_la->show();
        m_ui->groupBox_vm->show();
        m_ui->groupBox_pwm->show();
        m_ui->groupBox_sgen->show();
        m_ui->groupBox_cntr->show();

        m_connected = true;
    }
    else
    {
        QMessageBox msg("EMBO", "Serial port opening failed!",
                       QMessageBox::Warning, QMessageBox::Ok | QMessageBox::Default,
                       QMessageBox::NoButton, QMessageBox::NoButton);
        msg.setWindowIcon(QIcon(":/resources/img/icon.png"));
        msg.exec();
    }
    m_ui->pushButton_Connect->setText("Connect");
    m_ui->pushButton_Connect->setEnabled(true);
}

void MainWindow::on_pushButton_Disconnect_clicked()
{
    m_serial->close();

    m_ui->pushButton_Disconnect->hide();
    m_ui->pushButton_Connect->show();

    QLabel *status_txt = m_ui->statusbar->findChild<QLabel*>("status_txt");
    status_txt->setText(" Disconnected");
    m_status_icon->setPixmap(m_plug_off);

    m_ui->listWidget_ports->setEnabled(true);
    m_ui->pushButton_Scan->setEnabled(true);
    m_ui->groupBox_scope->hide();
    m_ui->groupBox_la->hide();
    m_ui->groupBox_vm->hide();
    m_ui->groupBox_pwm->hide();
    m_ui->groupBox_sgen->hide();
    m_ui->groupBox_cntr->hide();

    m_connected = false;
}




void MainWindow::on_serial_errorOccurred(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError) {
        QMessageBox::critical(this, tr("Critical Error"), m_serial->errorString());
        //closeSerialPort();
    }
}

void MainWindow::on_serial_readyRead()
{
    const QByteArray data = m_serial->readAll();
    QString str = QString::fromUtf8(data);
    qInfo() << str;
}
