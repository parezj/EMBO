/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "core.h"
#include "utils.h"
#include "msg.h"

#include <QObject>
#include <QDebug>
#include <QTimer>
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>


/******************************** Messages ********************************/

void Msg_Idn::on_dataRx()
{
    qInfo() << "IDN: " << rxData;
    auto core = Core::getInstance(this);

    QStringList tokens = rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    try
    {
        core->devInfo->name = tokens[1];
        core->devInfo->fw = tokens[2];
    }
    catch (...)
    {
        core->err(INVALID_MSG, true);
    }
}

void Msg_Rst::on_dataRx()
{
    qInfo() << "RST: " << rxData;
    auto core = Core::getInstance(this);

    if (!rxData.contains(EMBO_OK))
        core->err(INVALID_MSG, true);
}

void Msg_Sys_Lims::on_dataRx()
{
    qInfo() << "LIM: " <<  rxData;
    auto core = Core::getInstance(this);

    QStringList tokens = rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    try
    {
        core->devInfo->adc_fs_12b = tokens[0].toInt();
        core->devInfo->adc_fs_8b = tokens[1].toInt();
        core->devInfo->mem = tokens[2].toInt();
        core->devInfo->la_fs = tokens[3].toInt();
        core->devInfo->pwm_fs = tokens[4].toInt();
        core->devInfo->adc_num = (tokens[5])[0].digitValue();
        core->devInfo->adc_dualmode = tokens[5].contains('D');
        core->devInfo->adc_interleaved = tokens[5].contains('I');
        core->devInfo->adc_bit8 = tokens[6] == '1';
        core->devInfo->dac = tokens[7] == '1';
        core->devInfo->vm_fs = tokens[8].toInt();
        core->devInfo->vm_mem = tokens[9].toInt();
        core->devInfo->cntr_freq = tokens[10].toInt();
        core->devInfo->cntr_timeout = tokens[11].toInt();
        core->devInfo->sgen_maxf = tokens[12].toInt();
        core->devInfo->sgen_maxmem = tokens[13].toInt();
    }
    catch (...)
    {
        core->err(INVALID_MSG, true);
    }
}


void Msg_Sys_Info::on_dataRx()
{
    qInfo() << "INFO: " <<  rxData;
    auto core = Core::getInstance(this);

    QStringList tokens = rxData.split(EMBO_DELIM2, Qt::SkipEmptyParts);

    try
    {
        core->devInfo->rtos = tokens[0];
        core->devInfo->ll = tokens[1];
        core->devInfo->comm = tokens[2];
        core->devInfo->fcpu = tokens[3].toInt();
        core->devInfo->ref_mv = tokens[4].toInt();
        core->devInfo->pins_scope_vm = tokens[5];
        core->devInfo->pins_la = tokens[6];
        core->devInfo->pins_cntr = tokens[7];
        core->devInfo->pins_pwm = tokens[8];
        core->devInfo->pins_sgen = tokens[9];
    }
    catch (...)
    {
        core->err(INVALID_MSG, true);
    }
}

/********************************* Core *********************************/

Core* Core::m_instance = Q_NULLPTR;

Core::Core(QObject* parent) : QObject(parent)
{
    m_serial = new QSerialPort(this);
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    m_timer_rxTimeout = new QTimer(this);
    m_timer_render = new QTimer(this);
    m_timer_comm = new QTimer(this);

    m_msg_idn = new Msg_Idn(this);
    m_msg_rst = new Msg_Rst(this);
    m_msg_sys_lims = new Msg_Sys_Lims(this);
    m_msg_sys_info = new Msg_Sys_Info(this);

    devInfo = new DevInfo(this);

    connect(m_serial, &QSerialPort::errorOccurred, this, &Core::on_serial_errorOccurred);
    connect(m_serial, &QSerialPort::readyRead, this, &Core::on_serial_readyRead);

    connect(m_timer_rxTimeout, &QTimer::timeout, this, &Core::on_timer_rxTimeout);
    connect(m_timer_comm, &QTimer::timeout, this, &Core::on_timer_comm);
    connect(m_timer_render, &QTimer::timeout, this, &Core::on_timer_render);
}

Core::~Core()
{
}

bool Core::open(QString port)
{
    m_serial->setPortName(port);

    if (m_serial->open(QIODevice::ReadWrite))
    {
        m_state = CONNECTING;
        m_serial->flush();
        m_mainBuffer.clear();
        m_activeMsgs.clear();

        assert(m_activeMsgs.isEmpty());
        m_activeMsgs.append(m_msg_idn);
        m_activeMsgs.append(m_msg_sys_lims);
        m_activeMsgs.append(m_msg_sys_info);
        send();

        return true;
    }
    else
    {
        m_state = DISCONNECTED;
        return false;
    }
}

bool Core::close()
{
    m_state = DISCONNECTED;
    m_serial->close(); // TODO enque
    m_timer_rxTimeout->stop();
    m_timer_comm->stop();
    m_timer_render->stop();

    emit stateChanged(m_state);
    return true;
}

void Core::start()
{
    m_state = CONNECTED;
    emit stateChanged(m_state);
    m_timer_comm->start(TIMER_COMM);
    m_timer_render->start(TIMER_RENDER);
}

void Core::err(QString name, bool needClose)
{
    emit errorHappend(name);
    if (needClose)
        close();
}

QString Core::getPort()
{
    return m_serial->portName();
}

/* private */

void Core::send()
{
    assert(m_activeMsgs.size() > 0);

    QString tx;
    int it = 0;

    for(Msg* msg : m_activeMsgs)
    {
        if (it > 0)
            tx.append(EMBO_DELIM1);
        tx.append(msg->getTxData());
        it++;
    }
    tx.append(EMBO_NEWLINE);

    m_serial->write(tx.toStdString().c_str(), tx.size());

    qInfo() << "sent: " << tx;
    m_timer_rxTimeout->start(TIMER_RX);
}

void Core::on_serial_errorOccurred(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
        err(m_serial->errorString(), true);
}

void Core::on_serial_readyRead()
{
    try
    {
        const QByteArray data = m_serial->readAll();
        QString str = QString::fromUtf8(data);

        m_mainBuffer = m_mainBuffer.append(data);
        QStringList messages = m_mainBuffer.split(EMBO_NEWLINE, Qt::SkipEmptyParts);

        //qInfo() << "rx buffer: " << m_mainBuffer;

        for(int i = 0; i < m_mainBuffer.count(EMBO_NEWLINE); i++) // iterate all full msgs
        {
            qInfo() << "rx msg: " << messages[i];

            m_mainBuffer = m_mainBuffer.right(m_mainBuffer.size() - (messages[i].size() + 2));

            if (messages[i] == EMBO_READY_A || messages[i] == EMBO_READY_A || messages[i] == EMBO_READY_A)
            {
                // emit READY signal
                continue;
            }
            QStringList submessages = messages[i].split(EMBO_DELIM1, Qt::SkipEmptyParts);

            m_submsgIt = 0;
            for(const QString submessage : submessages)
            {
                if (m_state == DISCONNECTED)
                    return;
                m_activeMsgs[m_submsgIt++]->fire(submessage); // do main actions
            }
            if (m_submsgIt == m_activeMsgs.size()) // success - do post actions
            {
                m_submsgIt = 0;
                m_timer_rxTimeout->stop();
                m_activeMsgs.clear();

                if (m_state == CONNECTING)
                    start();
                else if (m_state == CONNECTED)
                    m_timer_comm->start();
            }
        }
    }
    catch (...)
    {
        std::exception_ptr p = std::current_exception();
        err((p ? p.__cxa_exception_type()->name() : "exception raised"), true);
    }
}

void Core::on_timer_rxTimeout()
{
    err("Communication timeout!", true);
}

void Core::on_timer_comm()
{
    //m_timer_rxTimeout->stop();

    //assert(m_activeMsgs.isEmpty());
    if (!m_activeMsgs.isEmpty())
        return;

    // TODO

    if (m_activeMsgs.isEmpty())
        m_activeMsgs.append(m_msg_idn);

    send();
}

void Core::on_timer_render()
{

}
