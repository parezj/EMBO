/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef UTILS_H
#define UTILS_H

#include <QString>
#include <QPainter>

QString format_unit(double value, QString unit, int precision);

double lin_to_exp_1to36M(double x, bool inverse = false);

double sinc(const double x);



static QVector<qreal> firstControlPoints(const QVector<qreal>& vector);
static QVector<QPointF> calculateControlPoints(const QVector<QPointF> &points);
QPainterPath splineFromPoints(const QVector<QPointF> &points, int penWidth);

#endif // UTILS_H
