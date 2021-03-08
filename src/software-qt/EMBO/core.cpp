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
#include <QSettings>
#include <QtSerialPort>
#include <QtSerialPort/QSerialPortInfo>


Core* Core::m_instance = Q_NULLPTR;

Core::Core(QObject* parent) : QObject(parent)
{
}

Core::~Core()
{
    qInfo() << "Core destroyed";
}

void Core::on_startThread()
{
    m_serial = new QSerialPort();
    m_serial->setBaudRate(QSerialPort::Baud115200);
    m_serial->setDataBits(QSerialPort::Data8);
    m_serial->setParity(QSerialPort::NoParity);
    m_serial->setStopBits(QSerialPort::OneStop);
    m_serial->setFlowControl(QSerialPort::NoFlowControl);

    m_timer_rxTimeout = new QTimer();
    m_timer_render = new QTimer();
    m_timer_comm = new QTimer();

    m_timer_rxTimeout->setTimerType(Qt::PreciseTimer);
    m_timer_comm->setTimerType(Qt::PreciseTimer);
    m_timer_render->setTimerType(Qt::PreciseTimer);

    m_msg_idn = new Msg_Idn(this);
    m_msg_rst = new Msg_Rst(this);
    m_msg_stb = new Msg_Stb(this);
    m_msg_cls = new Msg_Cls(this);
    m_msg_dummy = new Msg_Dummy(this);
    m_msg_sys_lims = new Msg_SYS_Lims(this);
    m_msg_sys_info = new Msg_SYS_Info(this);
    m_msg_sys_mode = new Msg_SYS_Mode(this);

    /*
    m_msg_vm_read = new Msg_VM_Read(this);
    m_msg_scope_set = new Msg_SCOP_Set(this);
    m_msg_scope_read = new Msg_SCOP_Read(this);
    m_msg_scope_forcetrig = new Msg_SCOP_ForceTrig(this);
    m_msg_scope_average = new Msg_SCOP_Average(this);
    m_msg_la_set = new Msg_LA_Set(this);
    m_msg_la_read = new Msg_LA_Read(this);
    m_msg_la_forcetrig = new Msg_LA_ForceTrig(this);
    m_msg_cntr_enable = new Msg_CNTR_Enable(this);
    m_msg_cntr_read = new Msg_CNTR_Read(this);
    m_msg_sgen_set = new Msg_SGEN_Set(this);
    m_msg_pwm_set = new Msg_PWM_Set(this);
    */

    devInfo = new DevInfo(this);

    connect(m_serial, &QSerialPort::errorOccurred, this, &Core::on_serial_errorOccurred);
    connect(m_serial, &QSerialPort::readyRead, this, &Core::on_serial_readyRead);

    connect(m_timer_rxTimeout, &QTimer::timeout, this, &Core::on_timer_rxTimeout);
    connect(m_timer_comm, &QTimer::timeout, this, &Core::on_timer_comm);
    connect(m_timer_render, &QTimer::timeout, this, &Core::on_timer_render);

    qInfo() << "Core thread started";
}

bool Core::openComm(QString port)
{
    m_serial->setPortName(port);
    m_state = OPENING;
    emit stateChanged(m_state);

    if (m_serial->open(QIODevice::ReadWrite))
    {
        qInfo() << ">>Connected1<<";
        m_state = CONNECTING1;
        emit stateChanged(m_state);

        m_serial->clear();

        m_mainBuffer.clear();
        m_waitingMsgs.clear();
        m_activeMsgs.clear();

        assert(m_activeMsgs.isEmpty());
        m_activeMsgs.append(m_msg_dummy);

        send();

        return true;
    }
    else
    {
        err("Serial port opening failed!", true);
        m_state = DISCONNECTED;
        emit stateChanged(m_state);
        return false;
    }
}

void Core::openCommInit()
{
    m_open_comm = true;
}

bool Core::closeComm()
{
    m_state = DISCONNECTED;
    m_serial->close(); // TODO enque
    m_timer_rxTimeout->stop();
    m_timer_comm->stop();
    m_timer_render->stop();

    qInfo() << ">>Disconnected<<";
    emit stateChanged(m_state);
    return true;
}

void Core::startComm()
{
    qInfo() << ">>Connected2<<";
    m_state = CONNECTED;
    emit stateChanged(m_state);
    m_timer_comm->start(TIMER_COMM);
    m_timer_render->start(TIMER_RENDER);
}

void Core::err(QString name, bool needClose)
{
    emit msgDisplay(name, needClose ? CRITICAL : WARNING);
    qInfo() << "ERR: " + name;

    if (needClose)
        closeComm();
}

void Core::msgAdd(Msg* msg, bool isQuery, QString params)
{
    assert(msg != Q_NULLPTR);

    msg->setIsQuery(isQuery);
    if (!params.isEmpty())
        msg->setParams(params);

    m_waitingMsgs.append(msg);
}

/* private */

void Core::send()
{
    assert(m_activeMsgs.size() > 0);

    QString tx;
    int it = 0;

    for(auto msg : m_activeMsgs)
    {
        if (it > 0)
            tx.append(EMBO_DELIM1);

        tx.append( msg->getCmd() +
                  (msg->getIsQuery() ? "?" :
                        (msg->getParams().isEmpty() ? "" : " " + msg->getParams())));
        it++;
    }
    tx.append(EMBO_NEWLINE);

    m_serial->write(tx.toStdString().c_str(), tx.size());

    qInfo() << "sent: " << tx;
    m_timer_rxTimeout->start(TIMER_RX);
}

void Core::openComm2()
{
    m_open_comm = false;
    m_state = CONNECTING2;

    m_activeMsgs.append(m_msg_idn);
    m_activeMsgs.append(m_msg_sys_lims);
    m_activeMsgs.append(m_msg_sys_info);
    m_msg_sys_mode->setIsQuery(true);
    m_activeMsgs.append(m_msg_sys_mode);

    send();
}

/* slots */

void Core::on_openComm(const QString port)
{
    openComm(port);
}

/*
void Core::on_msgAdd(Msg* msg)
{
    msgAdd(msg);
}
*/

void Core::on_closeComm(bool force)
{
    if (force || m_state != CONNECTED)
        closeComm();
    else
        m_close_init = true;
}

void Core::on_dispose()
{
    if (m_state == CONNECTED)
        closeComm();
    emit finished();
    //this->thread()->quit();
}

/* private slots */

void Core::on_serial_errorOccurred(QSerialPort::SerialPortError error)
{
    if (error == QSerialPort::ResourceError)
        err(m_serial->errorString(), true);
}

void Core::on_serial_readyRead()
{
    try // exceptions DO NOT work
    {
        const QByteArray data = m_serial->readAll();
        QString str = QString::fromUtf8(data);

        m_mainBuffer = m_mainBuffer.append(data);
        QStringList messages = m_mainBuffer.split(EMBO_NEWLINE, Qt::SkipEmptyParts);

        //qInfo() << "rx buffer: " << m_mainBuffer;
        m_timer_rxTimeout->stop();
        m_timer_rxTimeout->start();

        for(int i = 0; i < m_mainBuffer.count(EMBO_NEWLINE); i++) // iterate all full msgs
        {
            //qInfo() << "rx msg: " << messages[i];

            m_mainBuffer = m_mainBuffer.right(m_mainBuffer.size() - (messages[i].size() + 2));

            if (messages[i] == EMBO_READY_A || messages[i] == EMBO_READY_N || messages[i] == EMBO_READY_D)
            {
                // emit READY signal                
                continue;
            }
            QStringList submessages = messages[i].split(EMBO_DELIM1, Qt::SkipEmptyParts);

            m_submsgIt = 0;
            int activeMsg_size = m_activeMsgs.size();

            for(const QString submessage : submessages)
            {
                if (m_state == DISCONNECTED)
                    return;
                if (m_submsgIt >= activeMsg_size)
                {
                    err(COMM_FATAL_ERR + messages[i] + m_mainBuffer, true);
                    return;
                }

                m_activeMsgs[m_submsgIt++]->fire(submessage); // do main virtual action
            }

            if (m_submsgIt == activeMsg_size) // success - do post actions
            {
                m_submsgIt = 0;
                m_timer_rxTimeout->stop();
                m_activeMsgs.clear();

                if (m_state == CONNECTING2)
                    startComm();
                else if (m_state == CONNECTED)
                    m_timer_comm->start();
            }
        }
        if (m_open_comm)
            openComm2();
    }
    catch (const std::exception& ex)
    {
        std::exception_ptr p = std::current_exception();
        err((p ? p.__cxa_exception_type()->name() : " exception raised"), true);
    }
    catch (...)
    {
        err("exception raised", true);
    }
}

void Core::on_timer_rxTimeout()
{
    err("Communication timeout!", true);
}

void Core::on_timer_comm()
{
    if (m_close_init)
    {
        m_close_init = false;
        closeComm();
        return;
    }

    if (!m_activeMsgs.isEmpty())
    {
        qInfo() << "Communication is throttling!";
        return;
    }

    if (m_mode != m_mode_last)
    {
        m_msg_sys_mode->setIsQuery(false);
        m_msg_sys_mode->setParams(m_mode == LA ? "LA" : (m_mode == SCOPE ? "SCOPE" : "VM"));
        m_activeMsgs.append(m_msg_sys_mode);
    }
    m_mode_last = m_mode;

    int waitingSize = m_waitingMsgs.size();
    if (waitingSize > 0)
    {
        m_activeMsgs.append(m_waitingMsgs.mid(0, waitingSize));
        m_waitingMsgs.remove(0, waitingSize);
    }

    for (auto instr : emboInstruments)
    {
        auto activeMsg = instr->getActiveMsg();
        if (activeMsg != Q_NULLPTR)
            m_activeMsgs.append(activeMsg);
    }

    if (m_activeMsgs.isEmpty())
    {
        m_activeMsgs.append(m_msg_stb);
        m_activeMsgs.append(m_msg_cls);
    }

    send();
}

void Core::on_timer_render()
{

}
