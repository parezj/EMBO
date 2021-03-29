/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef UTILS_H
#define UTILS_H

#include "containers.h"

#include <QString>
#include <QPainter>
#include <QMainWindow>


QString format_unit(double value, QString unit, int precision);
double lin_to_exp_1to36M(double x, bool inverse = false);
void msgBox(QMainWindow* window, QString text, MsgBoxType type);

#endif // UTILS_H
