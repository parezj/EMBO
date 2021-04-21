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
double lin_to_exp_1to1M(double x, bool inverse = false);

void msgBox(QMainWindow* window, QString text, MsgBoxType type);

int get_vals_from_circ(int from, int total, int bufflen, DaqBits daq_bits, double vcc, uint8_t* buff,
                       QVector<double>* ch1, QVector<double>* ch2, QVector<double>* ch3, QVector<double>* ch4,
                       double gain1, double gain2, double gain3, double gain4,
                       double offset1, double offset2, double offset3, double offset4);

const QString h_manual_to_auto(double fs, int mem, double& div_format, double& div_sec);

#endif // UTILS_H
