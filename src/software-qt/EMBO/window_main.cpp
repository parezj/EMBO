/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window_main.h"
#include "ui_window_main.h"
#include "core.h"
#include "utils.h"
#include "settings.h"

#include <QDebug>
#include <QDir>
#include <QUrl>
#include <QDesktopServices>
#include <QDirIterator>
#include <QLabel>
#include <QGridLayout>
#include <QStatusBar>
#include <QMessageBox>
#include <QListView>
#include <QSpacerItem>
#include <QFontDatabase>
#include <QThread>
#include <QSettings>
#include <QtSerialPort/QSerialPortInfo>


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_ui(new Ui::MainWindow)
{
    m_ui->setupUi(this);

    QThread* t1 = new QThread(this);
    auto core = Core::getInstance();
    core->moveToThread(t1);

    qRegisterMetaType<State>("State");
    qRegisterMetaType<Msg>("Msg");

    connect(qApp, SIGNAL(aboutToQuit()), this, SLOT(on_close()));
    connect(core, &Core::stateChanged, this, &MainWindow::on_coreState_changed, Qt::QueuedConnection);
    connect(core, &Core::errorHappend, this, &MainWindow::on_coreError_happend, Qt::QueuedConnection);
    connect(this, &MainWindow::open, core, &Core::on_open, Qt::QueuedConnection);
    connect(this, &MainWindow::close, core, &Core::on_close, Qt::QueuedConnection);
    connect(t1, SIGNAL(started()), core, SLOT(on_start()));
    connect(core, SIGNAL(finished()), t1, SLOT(quit()));
    connect(core, SIGNAL(finished()), core, SLOT(deleteLater()));
    connect(t1, SIGNAL(finished()), t1, SLOT(deleteLater()));

    t1->start();

    m_ui->pushButton_disconnect->hide();
    m_ui->groupBox_scope->hide();
    m_ui->groupBox_la->hide();
    m_ui->groupBox_vm->hide();
    m_ui->groupBox_pwm->hide();
    m_ui->groupBox_sgen->hide();
    m_ui->groupBox_cntr->hide();

    QStringList addedFonts = addFontsFromResources();
    for ( const QString& font : addedFonts )
        qInfo() << "Added font: " << font;

    //QFont font("Roboto");
    //QApplication::setFont(font);

    statusBarLoad();

    QString style1 = "QGroupBox {background-color: rgb(238,238,238);border: 1px solid gray; border-radius: 5px;  margin-top: 0.5em;}; \
                      QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}";

    //QString style1b = "QGroupBox {background-color: rgb(238,238,238);border: 1px solid gray; border-radius: 0px;  margin-top: 0.5em;}; \
    //                  QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}";

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

    on_pushButton_scan_clicked();
}

MainWindow::~MainWindow()
{
    delete m_ui;
}

/* slots */

void MainWindow::on_close()
{
    if (m_connected)
        emit close();
    Core::getInstance()->dispose();
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

void MainWindow::on_pushButton_scan_clicked()
{
    m_ui->listWidget_ports->clear();

    for(const QSerialPortInfo port : QSerialPortInfo::availablePorts())
        m_ui->listWidget_ports->addItem(port.portName());

    if (m_ui->listWidget_ports->children().count() > 0)
        m_ui->listWidget_ports->setCurrentRow(0);

    m_ui->pushButton_connect->setEnabled(m_ui->listWidget_ports->children().count() > 0);

    loadSettings();
}

void MainWindow::on_pushButton_connect_clicked()
{
    m_ui->listWidget_ports->setEnabled(false);
    m_ui->pushButton_scan->setEnabled(false);
    m_ui->pushButton_connect->setText("Wait");
    m_ui->pushButton_connect->setEnabled(false);

    QLabel *status_comm = m_ui->statusbar->findChild<QLabel*>("status_comm");
    status_comm->setText(" Connecting...");

    QString selPort = m_ui->listWidget_ports->currentIndex().data().toString();
    saveSettings();

    emit open(selPort);
}

void MainWindow::on_pushButton_disconnect_clicked()
{
    m_ui->pushButton_connect->setText("Wait");
    m_ui->pushButton_connect->setEnabled(false);

    emit close();
}

void MainWindow::on_coreState_changed(const State newState)
{
    if (newState == CONNECTED)
    {
        setConnected();
    }
    else if (newState == DISCONNECTED)
    {
        setDisconnected();
    }
    m_state_old = newState;
}

void MainWindow::on_coreError_happend(const QString name)
{
    QMessageBox msg("EMBO", name,
                   QMessageBox::Warning, QMessageBox::Ok | QMessageBox::Default,
                   QMessageBox::NoButton, QMessageBox::NoButton);
    msg.setWindowIcon(QIcon(":/main/resources/img/icon.png"));
    msg.exec();
}

/* private */

void MainWindow::statusBarLoad()
{
    m_status_icon_comm = new QLabel(this);
    QLabel* status_comm = new QLabel(" Disconnected ");
    QSpacerItem* status_spacer = new QSpacerItem(1, 1, QSizePolicy::Expanding, QSizePolicy::Preferred);
    QLabel* status_ctu = new QLabel("CTU FEE - 2021  ");
    QLabel* status_icon_jp = new QLabel(this);
    QLabel* status_author = new QLabel("&nbsp;&nbsp;<a href='https://www.jakubparez.com' style='color:black'>Jakub Pařez</a> ");
    status_author->connect(status_author, &QLabel::linkActivated, [](const QString &link) {
        QDesktopServices::openUrl(QUrl(link));
    });

    QWidget* widget = new QWidget();
    QFont font1("Roboto", 11, QFont::Normal);

    status_comm->setObjectName("status_comm");
    status_comm->setFont(font1);
    status_ctu->setFont(font1);
    status_author->setFont(font1);

    m_icon_plugOn = QPixmap(":/main/resources/img/plug_on.png");
    m_icon_plugOff = QPixmap(":/main/resources/img/plug_off.png");
    m_img_bluepill = QPixmap(":/main/resources/img/bluepill2.png");
    m_img_nucleoF303 = QPixmap(":/main/resources/img/nucleo-f303.png");
    m_img_unknown = QPixmap(":/main/resources/img/unknown2.png");
    QPixmap icon_jp = QPixmap(":/main/resources/img/jp.png");

    m_status_icon_comm->setPixmap(m_icon_plugOff);
    m_status_icon_comm->setFixedWidth(15);
    m_status_icon_comm->setFixedHeight(18);
    m_status_icon_comm->setScaledContents(true);
    status_icon_jp->setPixmap(icon_jp);
    status_icon_jp->setFixedWidth(17);
    status_icon_jp->setFixedHeight(17);
    status_icon_jp->setScaledContents(true);

    QGridLayout * layout = new QGridLayout(widget);
    layout->addWidget(m_status_icon_comm,0,0,1,1,Qt::AlignVCenter);
    layout->addWidget(status_comm,0,1,1,1,Qt::AlignVCenter | Qt::AlignLeft);
    layout->addItem(status_spacer,0,2,1,1,Qt::AlignVCenter);
    layout->addWidget(status_ctu,0,3,1,1,Qt::AlignVCenter);
    layout->addWidget(status_icon_jp,0,4,1,1,Qt::AlignVCenter);
    layout->addWidget(status_author,0,5,1,1,Qt::AlignVCenter);
    layout->setMargin(0);
    layout->setSpacing(0);
    m_ui->statusbar->addWidget(widget,1);
    m_ui->statusbar->setSizeGripEnabled(false);
}

QStringList MainWindow::addFontsFromResources(const QStringList& filters)
{
    QStringList addedFonts;
    QDirIterator iter(QStringLiteral(":/fonts"), filters, QDir::Files|QDir::Readable, QDirIterator::Subdirectories);
    while (iter.hasNext())
    {
        const QString& entry = iter.next();
        if ( QFontDatabase::addApplicationFont(entry) >= 0 )
            addedFonts << entry;
    }
    return addedFonts;
}

void MainWindow::loadSettings()
{
  QString port_saved = Settings::getValue("main/port", "").toString();

  for(int i = 0; i < m_ui->listWidget_ports->count(); ++i)
  {
      if (m_ui->listWidget_ports->item(i)->text() == port_saved)
          m_ui->listWidget_ports->setCurrentRow(i);
  }
}

void MainWindow::saveSettings()
{
    Settings::setValue("main/port", m_ui->listWidget_ports->currentIndex().data().toString());
}

void MainWindow::setConnected()
{
    m_ui->pushButton_connect->hide();
    m_ui->pushButton_disconnect->show();

    QLabel *status_comm = m_ui->statusbar->findChild<QLabel*>("status_comm");
    status_comm->setText(" Connected (" + Core::getInstance()->getPort() + ")");
    m_status_icon_comm->setPixmap(m_icon_plugOn);
    m_ui->label_boardImg->setPixmap(m_img_nucleoF303);

    m_ui->groupBox_scope->show();
    m_ui->groupBox_la->show();
    m_ui->groupBox_vm->show();
    m_ui->groupBox_pwm->show();
    m_ui->groupBox_sgen->show();
    m_ui->groupBox_cntr->show();

    auto info = Core::getInstance()->getDevInfo();

    m_ui->label_deviceName->setText(info->name);
    m_ui->label_dev_fw->setText(info->fw);
    m_ui->label_dev_ll->setText(info->ll);
    m_ui->label_dev_fcpu->setText(QString::number(info->fcpu) + " MHz");
    m_ui->label_dev_rtos->setText(info->rtos);
    m_ui->label_dev_comm->setText(info->comm);
    m_ui->label_dev_vref->setText(QString::number(info->ref_mv) + " mV");
    if (info->name.toLower().contains("bluepill"))
        m_ui->label_boardImg->setPixmap(m_img_bluepill);
    else if (info->name.toLower().contains("nucleo"))
        m_ui->label_boardImg->setPixmap(m_img_nucleoF303);

    m_ui->label_scope_fs->setText(format_unit(info->adc_fs_12b, "Sps"));
    m_ui->label_scope_mem->setText(format_unit((info->mem / 2) / (1 * 2), "B") +
                                   (info->adc_bit8 ? " / " + format_unit(info->mem / (1 * 2), "B") : ""));
    m_ui->label_scope_bits->setText(info->adc_bit8 ? "12 / 8 bit" : "12 bit");
    m_ui->label_scope_modes->setText("4ch " + QString::number(info->adc_num) + "ADC " + (info->adc_dualmode ? "D" : "") +
                                     (info->adc_dualmode && info->adc_interleaved ? "+" : "") + (info->adc_interleaved ? "I" : ""));
    m_ui->label_scope_pins->setText(info->pins_scope_vm.replace("-", ", "));

    m_ui->label_la_fs->setText(format_unit(info->la_fs, "Sps"));
    m_ui->label_la_mem->setText(format_unit(info->mem, "B"));
    m_ui->label_la_protocols->setText("Serial, I2C, SPI");
    m_ui->label_la_pins->setText(info->pins_la.replace("-", ", "));

    m_ui->label_vm_fs->setText(format_unit(info->vm_fs, "Sps"));
    m_ui->label_vm_mem->setText(format_unit(info->vm_mem, "S"));
    m_ui->label_vm_bits->setText("12 bit");
    m_ui->label_vm_pins->setText(info->pins_scope_vm.replace("-", ", "));

    m_ui->label_cntr_freq->setText(format_unit(info->cntr_freq, "Hz"));
    m_ui->label_cntr_timeout->setText(QString::number(info->cntr_timeout) + " ms");
    m_ui->label_cntr_pins->setText(info->pins_cntr);

    m_ui->label_pwm_freq->setText(format_unit(info->pwm_fs, "Hz"));
    m_ui->label_pwm_pins->setText(info->pins_pwm.replace("-", ", "));

    if (info->dac)
    {
        m_ui->label_sgen_freq->setText(format_unit(info->sgen_maxf, "Hz"));
        m_ui->label_sgen_mem->setText(format_unit(info->sgen_maxmem, "S"));
        m_ui->label_sgen_pins->setText(info->pins_sgen);
        m_ui->groupBox_sgen->show();
    }
    else m_ui->groupBox_sgen->hide();

    m_connected = true;
}

void MainWindow::setDisconnected()
{
    m_ui->pushButton_connect->setText("Connect");
    m_ui->pushButton_connect->setEnabled(true);
    m_ui->pushButton_disconnect->hide();
    m_ui->pushButton_connect->show();

    QLabel *status_comm = m_ui->statusbar->findChild<QLabel*>("status_comm");
    status_comm->setText(" Disconnected");
    m_status_icon_comm->setPixmap(m_icon_plugOff);

    m_ui->listWidget_ports->setEnabled(true);
    m_ui->pushButton_scan->setEnabled(true);
    m_ui->groupBox_scope->hide();
    m_ui->groupBox_la->hide();
    m_ui->groupBox_vm->hide();
    m_ui->groupBox_pwm->hide();
    m_ui->groupBox_sgen->hide();
    m_ui->groupBox_cntr->hide();

    m_ui->label_deviceName->setText("NOT CONNECTED");
    m_ui->label_dev_fw->setText("-");
    m_ui->label_dev_ll->setText("-");
    m_ui->label_dev_fcpu->setText("-");
    m_ui->label_dev_rtos->setText("-");
    m_ui->label_dev_comm->setText("-");
    m_ui->label_dev_vref->setText("-");
    m_ui->label_boardImg->setPixmap(m_img_unknown);

    m_ui->label_scope_fs->setText("-");
    m_ui->label_scope_mem->setText("-");
    m_ui->label_scope_bits->setText("-");
    m_ui->label_scope_modes->setText("-");
    m_ui->label_scope_pins->setText("-");

    m_ui->label_la_fs->setText("-");
    m_ui->label_la_mem->setText("-");
    m_ui->label_la_protocols->setText("-");
    m_ui->label_la_pins->setText("-");

    m_ui->label_vm_fs->setText("-");
    m_ui->label_vm_mem->setText("-");
    m_ui->label_vm_bits->setText("-");
    m_ui->label_vm_pins->setText("-");

    m_ui->label_cntr_freq->setText("-");
    m_ui->label_cntr_timeout->setText("-");
    m_ui->label_cntr_pins->setText("-");

    m_ui->label_pwm_freq->setText("-");
    m_ui->label_pwm_pins->setText("-");

    m_ui->label_sgen_freq->setText("-");
    m_ui->label_sgen_mem->setText("-");
    m_ui->label_sgen_pins->setText("-");

    m_connected = false;
}

