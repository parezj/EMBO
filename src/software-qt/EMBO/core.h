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

/******************************** Protocol ********************************/

#define EMBO_NEWLINE    "\r\n"
#define EMBO_DELIM1     ";"
#define EMBO_DELIM2     ","

#define EMBO_IDN        "*IDN?"
#define EMBO_LIMS       "SYS:LIM?"
#define EMBO_RST        "*RST"

#define EMBO_READY_A    "ReadyA"
#define EMBO_READY_N    "ReadyD"
#define EMBO_READY_D    "ReadyA"


/******************************** Messages ********************************/

class MsgIdn : public Msg
{
public:
    explicit MsgIdn(QObject* parent=0) : Msg(EMBO_IDN, parent) {};
    virtual void on_dataRx();
};

class MsgLims : public Msg
{
public:
    explicit MsgLims(QObject* parent=0) : Msg(EMBO_LIMS, parent) {};
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

    QString name = "";
    QString fw = "";
    QString rtos = ""; // TODO
    QString ll = ""; // TODO
    QString comm = ""; // TODO
    QString fcpu = ""; // TODO

    double adc_1ch_smpl_time12;
    double adc_1ch_smpl_time8;
    int mem;
    int la_fs;
    int pwm_fs;
    int adc_num;
    bool adc_dualmode;
    bool adc_interleaved;
    bool adc_bit8;
    bool dac;
    int ref_mv; // TODO
    int vm_mem; // TODO
    int vm_fs; // TODO
    int cntr_freq;// TODO
    int cntr_timeout;// TODO
    int sgen_maxf;// TODO
    int sgen_maxmem;// TODO

    QString pins_scope = "";  // TODO
    QString pins_la = "";  // TODO
    QString pins_cntr = "";  // TODO
    QString pins_pwm = "";  // TODO
    QString pins_sgen = "";  // TODO
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
    MsgIdn* m_msg_idn;
    MsgLims* m_msg_lims;
};

#endif // CORE_H
