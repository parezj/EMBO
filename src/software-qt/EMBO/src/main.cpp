/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "window__main.h"
#include "settings.h"

#include <QApplication>
#include <QStyleFactory>


int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QApplication::setStyle(QStyleFactory::create("Fusion"));
    Settings settings;
    WindowMain w;
    w.show();
    return a.exec();
}