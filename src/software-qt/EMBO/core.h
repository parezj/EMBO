/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CORE_H
#define CORE_H

#include "window_scope.h"
#include "window_la.h"
#include "window_vm.h"
#include "window_cntr.h"
#include "window_pwm.h"
#include "window_sgen.h"

#include "msg.h"
#include "messages.h"

#include <QObject>
#include <QTimer>
#include <QString>
#include <QSerialPort>
#include <QVector>

#define TIMER_RX        2000
#define TIMER_COMM      20
#define TIMER_RENDER    25

#define INVALID_MSG     "Invalid message! "
#define COMM_FATAL_ERR  "Communication fatal error! "

#define EMBO_TITLE      "EMBO"
#define EMBO_TITLE2     "EMBedded Oscilloscope"
#define EMBO_ABOUT_TXT  "<b>EMBO - EMBedded Oscilloscope</b><br><br> EMBO is useful tool for every electronics enthusiast.<br>\
For just few dollar hardware (STM32 BluePill) can become a powerfull scope, logic analyzer, voltmeter, counter, \
PWM and signal generator.<br>And of course, it's opensource!<br><br>\
<a href='https://github.com/parezj/EMBO'>github.com/parezj/EMBO</a>"

#define CFG_MAIN_PORT   "main/port"

#define EMBO_NEWLINE        "\r\n"
#define EMBO_DELIM1         ";"
#define EMBO_DELIM2         ","

#define EMBO_TRUE           "\"1\""
#define EMBO_FALSE          "\"0\""
#define EMBO_OK             "\"OK\""

#define EMBO_READY_A        "ReadyA"
#define EMBO_READY_N        "ReadyD"
#define EMBO_READY_D        "ReadyA"

enum State
{
    DISCONNECTED,
    OPENING,
    CONNECTING,
    CONNECTED
};

enum Mode
{
    VM,
    SCOPE,
    LA
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

    void setUp();
    bool openComm(QString port);
    bool closeComm();
    void startComm();
    void err(QString name, bool needClose);
    void msgAdd(Msg* msg);

    QVector<IEmboInstrument*> emboInstruments;

     /* setters getters */
    const QString getPort() { return m_serial->portName(); }
    DevInfo* getDevInfo() const { return devInfo; }
    void setMode(Mode mode, bool alsoLast) { m_mode = mode; if (alsoLast) m_mode_last = mode; }

     /* singleton */
    static Core* getInstance(QObject* parent = 0)
    {
        if (m_instance == Q_NULLPTR)
            m_instance = new Core(parent);
        return m_instance;
    }

public slots:
    void on_startThread();
    void on_openComm(const QString port);
    //void on_msgAdd(Msg* msg);
    void on_closeComm(bool force);
    void on_dispose();

signals:
    void stateChanged(const State state);
    void msgDisplay(const QString name, MsgBoxType type);
    void finished();

private slots:
    void on_serial_errorOccurred(QSerialPort::SerialPortError error);
    void on_serial_readyRead();
    void on_timer_rxTimeout();
    void on_timer_comm();
    void on_timer_render();

private:
    explicit Core(QObject* parent = 0);

    void send();

    /* instance */
    static Core* m_instance;

    QSerialPort* m_serial = Q_NULLPTR;
    State m_state = DISCONNECTED;

    /* helpers */
    bool close_init = false;
    Mode m_mode;
    Mode m_mode_last;

    /* timers */
    QTimer* m_timer_rxTimeout;
    QTimer* m_timer_render;
    QTimer* m_timer_comm;

    /* data */
    DevInfo* devInfo; // TODO const

    /* message buffers */
    QVector<Msg*> m_waitingMsgs;
    QVector<Msg*> m_activeMsgs;
    QString m_mainBuffer = "";
    int m_submsgIt = 0;

    /* message objects */
    Msg_Idn* m_msg_idn;
    Msg_Rst* m_msg_rst;
    Msg_SYS_Lims* m_msg_sys_lims;
    Msg_SYS_Info* m_msg_sys_info;
    Msg_SYS_Mode* m_msg_sys_mode;

    /*
    Msg_VM_Read* m_msg_vm_read;
    Msg_SCOP_Set* m_msg_scope_set;
    Msg_SCOP_Read* m_msg_scope_read;
    Msg_SCOP_ForceTrig* m_msg_scope_forcetrig;
    Msg_SCOP_Average* m_msg_scope_average;
    Msg_LA_Set* m_msg_la_set;
    Msg_LA_Read* m_msg_la_read;
    Msg_LA_ForceTrig* m_msg_la_forcetrig;
    Msg_CNTR_Enable* m_msg_cntr_enable;
    Msg_CNTR_Read* m_msg_cntr_read;
    Msg_SGEN_Set* m_msg_sgen_set;
    Msg_PWM_Set* m_msg_pwm_set;
    */
};

#endif // CORE_H
