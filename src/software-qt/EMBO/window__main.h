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
    void closeEvent(QCloseEvent *event);

    void on_actionAbout_triggered();
    void on_pushButton_scan_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();

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
    bool m_close_init = false;
    State m_state_old = DISCONNECTED;

    QPixmap m_icon_plugOn;
    QPixmap m_icon_plugOff;
    QPixmap m_img_bluepill;
    QPixmap m_img_nucleoF303;
    QPixmap m_img_unknown;
    QLabel* m_status_icon_comm;
    QLabel* m_status_comm;

    /* windows */
    WindowScope* m_w_scope = Q_NULLPTR;
    WindowLa* m_w_la = Q_NULLPTR;
    WindowVm* m_w_vm = Q_NULLPTR;
    WindowCntr* m_w_cntr = Q_NULLPTR;
    WindowPwm* m_w_pwm = Q_NULLPTR;
    WindowSgen* m_w_sgen = Q_NULLPTR;

    Ui::WindowMain* m_ui = Q_NULLPTR;
};
#endif // MAINWINDOW_H
