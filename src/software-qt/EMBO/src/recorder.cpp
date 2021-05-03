/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "recorder.h"

#include <QDir>
#include <QPixmap>
#include <QDateTime>
#include <QStandardPaths>


#define FILENAME_FORMAT    "yyyyMMdd_HHmmsszzz"


Recorder::Recorder(int precision) : m_precision(precision)
{
    reset();
}

void Recorder::reset()
{
    m_dir = QStandardPaths::writableLocation(QStandardPaths::DesktopLocation);
}

bool Recorder::setDir(const QString dir)
{
    if (m_recording)
        return false;

    if (!QDir(dir).exists())
        return QDir().mkdir(dir);

    return true;
}

bool Recorder::setDelim(Delim delim)
{
    if (m_recording)
        return false;

    m_delim = delim;

    if (m_delim == CSV) m_ext = ".csv";
    else if (m_delim == TAB || m_delim == SEMICOLON) m_ext = ".txt";
    //else if (m_delim == MAT) m_ext = ".mat";

    return true;
}

QString Recorder::generateFilePath(QString prefix, QString ext)
{
    m_file_name = "EMBO_" + prefix + "_" + QDateTime::currentDateTime().toString(FILENAME_FORMAT) + ext;
    m_file_path = pathCombine(m_dir, m_file_name);
    return m_file_path;
}

bool Recorder::createFile(QString prefix, QMap<QString,QString> header)
{
    generateFilePath(prefix, m_ext);

    m_file.setFileName(m_file_path);
    m_file.open(QIODevice::Append);
    if(m_file.isOpen())
    {
        m_stream.setDevice(&m_file);

        QMap<QString, QString>::iterator i;
        for (i = header.begin(); i != header.end(); ++i)
            (*this) << i.key() << i.value() << ENDL;

        m_recording = true;
        m_data_prev = false;
        return true;
    }
    return false;
}

QString Recorder::closeFile()
{
    m_file.flush();
    m_file.close();
    m_recording = false;

    return m_file_path;
}

QString Recorder::takeScreenshot(QString prefix, QWidget* widget)
{
    generateFilePath(prefix, ".png");

    QPixmap pixmap(widget->size());
    widget->render(&pixmap);

    QFile file(m_file_path);
    if (file.open(QIODevice::WriteOnly))
        if (pixmap.save(&file, "PNG"))
            return m_file_path;

    return "";
}

Recorder& Recorder::operator<<(int val)
{
    (*this) << QString::number(val);
    return (*this);
}

Recorder& Recorder::operator<<(double val)
{
    (*this) << QString::number(val, 10, m_precision);
    return (*this);
}

Recorder& Recorder::operator<<(QString val)
{
    if (m_data_prev)
        m_stream << (char)m_delim;

    m_stream << val;
    m_data_prev = true;

    return (*this);
}

Recorder& Recorder::operator<<(Specials special)
{
    if (special == ENDL)
    {
        m_data_prev = false;
        m_stream << '\n';   /* dont care about CR LF windows confusion */
    }

    return (*this);
}

QString Recorder::pathCombine(const QString& path1, const QString& path2)
{
    return QDir::cleanPath(path1 + QDir::separator() + path2);
}
