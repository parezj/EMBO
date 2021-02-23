#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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

private slots:
    void on_actionAbout_triggered();
    void on_actionOpen_triggered();
    void on_pushButton_Scan_clicked();
    void on_pushButton_Connect_clicked();
    void on_pushButton_Disconnect_clicked();

    void on_serial_errorOccurred(QSerialPort::SerialPortError error);
    void on_serial_readyRead();

private:
    bool m_connected = false;

    QPixmap m_plug_on;
    QPixmap m_plug_off;
    QLabel* m_status_icon;

    Ui::MainWindow *m_ui = nullptr;
    QSerialPort *m_serial = nullptr;
};
#endif // MAINWINDOW_H
