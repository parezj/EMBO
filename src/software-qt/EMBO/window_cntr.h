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
    void on_msg_err(QString text, MsgBoxType type, bool needClose);
    void on_msg_enable(bool isQuery, bool enable);
    void on_msg_read(QString freq, QString period);

    void on_actionAbout_triggered();
    void on_pushButton_disable_clicked();
    void on_pushButton_enable_clicked();

private:
    void closeEvent(QCloseEvent *event) override;
    void showEvent(QShowEvent* event) override;

    QLabel* m_status_enabled;

    Ui::WindowCntr* m_ui;

    /* messages */
    Msg_CNTR_Enable* m_msg_enable;
    Msg_CNTR_Read* m_msg_read;
};

#endif // WINDOW_CNTR_H
