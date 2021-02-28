/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef SETTINGS_H
#define SETTINGS_H


#include <QSettings>


class Settings
{
public:
    Settings();
    ~Settings();

    static bool contains(const QString &key);
    static QVariant getValue(const QString &key, const QVariant &defaultValue = QVariant());
    static void setValue(const QString &key, const QVariant &value);

private:
    static Settings *s_instance;
    QSettings* m_settings;
};

#endif // SETTINGS_H
