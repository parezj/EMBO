/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef WINDOW_CNTR_H
#define WINDOW_CNTR_H

#include "interfaces.h"
#include "messages.h"

#include <QString>
#include <QMainWindow>
#include <QLabel>
#include <QButtonGroup>


#define FREQ_TIMEOUT    "? Hz "
#define PERIOD_TIMEOUT  "? ms "


QT_BEGIN_NAMESPACE
namespace Ui { class WindowCntr; }
QT_END_NAMESPACE


class WindowCntr : public QMainWindow, public IEmboInstrument
{
    Q_OBJECT

public:
    explicit WindowCntr(QWidget *parent = nullptr);
    ~WindowCntr();

    bool getInstrEnabled() override { return m_instrEnabled; };
    Msg* getActiveMsg() override { return m_activeMsg; };

signals:
    void closing(const char* className);

private slots:
    void on_msg_ok(QString val1, QString val2);
    void on_msg_err(QString text, MsgBoxType type, bool needClose);
    void on_msg_enable(bool enabled, bool fastMode);
    void on_msg_read(QString freq, QString period);

    void on_actionAbout_triggered();
    void on_pushButton_disable_clicked();
    void on_pushButton_enable_clicked();

    void on_radioButton_precise_clicked();

    void on_radioButton_fast_clicked();

private:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;
    void enableAll(bool enable);
    void sendEnable(bool enable);

    QLabel* m_status_enabled;

    QButtonGroup m_mode;
    bool m_fastMode = false;
    bool m_enable_wantSwitch = false;

    Ui::WindowCntr* m_ui;

    /* messages */
    Msg_CNTR_Enable* m_msg_enable;
    Msg_CNTR_Read* m_msg_read;
};

#endif // WINDOW_CNTR_H
