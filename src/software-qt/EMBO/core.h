/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CORE_H
#define CORE_H

#include "msg.h"

#include <QObject>
#include <QTimer>
#include <QString>
#include <QSerialPort>
#include <QVector>

#define TIMER_RX        2000
#define TIMER_COMM      20
#define TIMER_RENDER    25

#define INVALID_MSG     "Invalid message!"

/******************************** Protocol ********************************/

#define EMBO_NEWLINE    "\r\n"
#define EMBO_DELIM1     ";"
#define EMBO_DELIM2     ","

#define EMBO_OK         "OK"

#define EMBO_IDN        "*IDN?"
#define EMBO_LIMS       ":SYS:LIM?"
#define EMBO_INFO       ":SYS:INFO?"
#define EMBO_RST        "*RST"

#define EMBO_READY_A    "ReadyA"
#define EMBO_READY_N    "ReadyD"
#define EMBO_READY_D    "ReadyA"


/******************************** Messages ********************************/

class Msg_Idn : public Msg
{
public:
    explicit Msg_Idn(QObject* parent=0) : Msg(EMBO_IDN, parent) {};
    virtual void on_dataRx();
};

class Msg_Rst : public Msg
{
public:
    explicit Msg_Rst(QObject* parent=0) : Msg(EMBO_RST, parent) {};
    virtual void on_dataRx();
};

class Msg_Sys_Lims : public Msg
{
public:
    explicit Msg_Sys_Lims(QObject* parent=0) : Msg(EMBO_LIMS, parent) {};
    virtual void on_dataRx();
};

class Msg_Sys_Info : public Msg
{
public:
    explicit Msg_Sys_Info(QObject* parent=0) : Msg(EMBO_INFO, parent) {};
    virtual void on_dataRx();
};



/********************************* Core *********************************/

enum State
{
    DISCONNECTED,
    CONNECTING,
    CONNECTED
};

class DevInfo : public QObject
{
Q_OBJECT
public:
    DevInfo(QObject* parent) : QObject(parent) { }

    /* IDN */
    QString name;
    QString fw;

    /* SYS:INFO */
    QString rtos;
    QString ll;
    QString comm;
    int fcpu;
    int ref_mv;
    QString pins_scope_vm;
    QString pins_la;
    QString pins_cntr;
    QString pins_pwm;
    QString pins_sgen;

    /* SYS:LIM */
    int adc_fs_12b;
    int adc_fs_8b;
    int mem;
    int la_fs;
    int pwm_fs;
    int adc_num;
    bool adc_dualmode;
    bool adc_interleaved;
    bool adc_bit8;
    bool dac;
    int vm_mem;
    int vm_fs;
    int cntr_freq;
    int cntr_timeout;
    int sgen_maxf;
    int sgen_maxmem;
};

class Core : public QObject
{
Q_OBJECT

public:
    ~Core();
    bool open(QString port);
    bool close();
    void start();
    void err(QString name, bool needClose);
    QString getPort();

    static Core* getInstance(QObject* parent = 0)
    {
        if (m_instance == Q_NULLPTR)
            m_instance = new Core(parent);
        return m_instance;
    }

    /* Data */
    DevInfo* devInfo; // TODO const

signals:
    void stateChanged(State state);
    void errorHappend(QString name);

private:
    explicit Core(QObject* parent = 0);

    void send();

    void on_serial_errorOccurred(QSerialPort::SerialPortError error);
    void on_serial_readyRead();
    void on_timer_rxTimeout();
    void on_timer_comm();
    void on_timer_render();

    static Core* m_instance;

    QSerialPort* m_serial = nullptr;
    State m_state = DISCONNECTED;

    QVector<Msg*> m_activeMsgs;
    QString m_mainBuffer = "";
    int m_submsgIt = 0;

    QTimer* m_timer_rxTimeout;
    QTimer* m_timer_render;
    QTimer* m_timer_comm;

    /* messages */
    Msg_Idn* m_msg_idn;
    Msg_Rst* m_msg_rst;
    Msg_Sys_Lims* m_msg_sys_lims;
    Msg_Sys_Info* m_msg_sys_info;
};

#endif // CORE_H
