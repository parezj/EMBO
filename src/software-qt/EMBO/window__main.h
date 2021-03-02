/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "core.h"

#include <QMainWindow>
#include <QSerialPort>
#include <QPixmap>
#include <QLabel>

#define CSS_INSTR_GROUP_SCOPE "QGroupBox {background-color: rgba(190,220,240,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_LA    "QGroupBox {background-color: rgba(240,190,190,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_VM    "QGroupBox {background-color: rgba(240,230,190,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_CNTR  "QGroupBox {background-color: rgba(200,220,200,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_PWM   "QGroupBox {background-color: rgba(220,200,180,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_SGEN  "QGroupBox {background-color: rgba(200,200,220,0.5);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_GROUP_OFF   "QGroupBox {background-color: rgb(238,238,238);border: 1px solid gray; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"

#define CSS_INSTR_BUTTON_ON   "QPushButton { \
                                   padding: 0.2em 0.2em 0.3em 0.2em; \
                                   border: 1px solid rgb(100, 100, 100); \
                                   border-radius: 5px; \
                                   background: qlineargradient(x1:0, y1:0, x2:0, y2:2, stop:0 #FFFFFF, stop:0.1 #FFFFFF, stop:1  #7B7B7B); \
                                   color: black; \
                               } \
                               QPushButton:hover:!pressed \
                               { \
                                   border: 1px solid black; \
                                   border-radius: 5px; \
                                   background: #FFFFFF; \
                               } \
                               QPushButton:pressed \
                               { \
                                   border: 1px solid black; \
                                   border-radius: 5px; \
                                   background: #888888; \
                                   color:white; \
                               }"

#define CSS_INSTR_BUTTON_OFF  "QPushButton {padding: 0.2em 0.2em 0.3em 0.2em; border: 0px; color: gray;}"

#define CSS_GROUP2            "QGroupBox {background-color: rgb(220,220,220);border: 0px; border-radius: 5px; margin-top: 0.5em;}; \
                               QGroupBox::title {subcontrol-origin: margin;left: 10px;padding: 0 3px 0 3px;}"


QT_BEGIN_NAMESPACE
namespace Ui { class WindowMain; }
QT_END_NAMESPACE


class WindowMain : public QMainWindow
{
    Q_OBJECT

public:
    WindowMain(QWidget *parent = nullptr);
    ~WindowMain();

signals:
    void openComm(const QString port);
    void closeComm(bool force);
    void disposeCore();

private slots:
    void on_actionAbout_triggered();
    void on_pushButton_scan_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();

    void on_close();
    void on_coreState_changed(const State newState);
    void on_msgDisplay(const QString text, MsgBoxType type);
    void on_instrClose(const char* className);

    void on_pushButton_scope_clicked();
    void on_pushButton_la_clicked();
    void on_pushButton_vm_clicked();
    void on_pushButton_cntr_clicked();
    void on_pushButton_pwm_clicked();
    void on_pushButton_sgen_clicked();

private:
    void instrFirstRowEnable(bool enable);
    QStringList addFontsFromResources(const QStringList& filters={QStringLiteral("*.ttf"),QStringLiteral("*.otf")});
    void statusBarLoad();
    void loadSettings();
    void saveSettings();
    void setConnected();
    void setDisconnected();

    bool m_connected = false;
    State m_state_old = DISCONNECTED;

    QPixmap m_icon_plugOn;
    QPixmap m_icon_plugOff;
    QPixmap m_img_bluepill;
    QPixmap m_img_nucleoF303;
    QPixmap m_img_unknown;
    QLabel* m_status_icon_comm;

    /* windows */
    WindowScope* w_scope = Q_NULLPTR;
    WindowLa* w_la = Q_NULLPTR;
    WindowVm* w_vm = Q_NULLPTR;
    WindowCntr* w_cntr = Q_NULLPTR;
    WindowPwm* w_pwm = Q_NULLPTR;
    WindowSgen* w_sgen = Q_NULLPTR;

    Ui::WindowMain* m_ui = Q_NULLPTR;
};
#endif // MAINWINDOW_H
