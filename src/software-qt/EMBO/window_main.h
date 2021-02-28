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
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

signals:
    void open(const QString port);
    void close();

private slots:
    void on_close();
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_pushButton_scan_clicked();
    void on_pushButton_connect_clicked();
    void on_pushButton_disconnect_clicked();

    void on_coreState_changed(const State newState);
    void on_coreError_happend(const QString name);

private:
    void loadSettings();
    void saveSettings();
    void setConnected();
    void setDisconnected();

    bool m_connected = false;
    State m_state_old = DISCONNECTED;

    QPixmap m_img_plugOn;
    QPixmap m_img_plugOff;
    QPixmap m_img_bluepill;
    QPixmap m_img_nucleoF303;
    QPixmap m_img_unknown;

    QLabel* m_status_icon;

    Ui::MainWindow *m_ui = nullptr;
};
#endif // MAINWINDOW_H
