/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef RECORDER_H
#define RECORDER_H

#include <QString>
#include <QMap>
#include <QFile>
#include <QMainWindow>
#include <QTextStream>

#include <limits>


enum Delim : char
{
    CSV         = ',',
    TAB         = '\t',
    SEMICOLON   = ';',
    //MAT // TODO
};

enum Specials
{
    ENDL
};

class Recorder
{
public:
    Recorder(int precision = 4);

    void reset();

    bool setDir(const QString dir);
    bool setDelim(Delim delim);

    QString getDir() const { return m_dir; }
    QString getFilePath() const { return m_file_path; }
    QString getFileName() const { return m_file_name; }
    Delim getDelim() const { return m_delim; }
    QString generateFilePath(QString prefix, QString ext);

    bool createFile(QString prefix, QMap<QString,QString> header);
    QString closeFile();

    QString takeScreenshot(QString prefix, QWidget* widget);

    Recorder& operator<<(int val);
    Recorder& operator<<(double val);
    Recorder& operator<<(QString val);
    Recorder& operator<<(Specials special);


private:
    QString pathCombine(const QString& path1, const QString& path2);

    int m_precision = 4;
    bool m_recording = false;
    bool m_data_prev = false;
    QFile m_file;
    QTextStream m_stream;

    QString m_dir = "";
    QString m_file_path = "";
    QString m_file_name = "";
    QString m_ext = ".csv";
    Delim m_delim = CSV;

};

#endif // RECORDER_H
