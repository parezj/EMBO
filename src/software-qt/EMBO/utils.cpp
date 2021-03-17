/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "utils.h"

#include <QString>
#include <QDebug>

#include <math.h>


QString format_unit(double value, QString unit, int precision)
{
    if (value < 0.000000001)
        return(QString::number(value * 1000000000000, 'd', precision) + " p" + unit);
    else if (value < 0.000001)
        return(QString::number(value * 1000000000, 'd', precision) + " n" + unit);
    else if (value < 0.001)
        return(QString::number(value * 1000000, 'd', precision) + " u" + unit);
    else if (value < 1)
        return(QString::number(value * 1000, 'd', precision) + " m" + unit);
    else if (value < 1000)
        return(QString::number(value * 1, 'd', precision) + " " + unit);
    else if (value < 1000000)
        return(QString::number(value * 0.001, 'd', precision) + " k" + unit);
    else if (value < 1000000000)
        return(QString::number(value * 0.000001, 'd', precision) + " M" + unit);
    else if (value < 1000000000000)
        return(QString::number(value * 0.000000001, 'd', precision) + " G" + unit);
    else
        return(QString::number(value * 0.000000000001, 'd', precision) + " T" + unit);
}

double lin_to_exp_1to36M(double x, bool inverse)
{
    const double a = 0.999999516693728;
    const double b = 0.0000004833063883257437;

    double ret = inverse ? ((a * log(x)) / b) : (a * exp(b * x));
    //qInfo() << ret;

    return ret;
}

double sinc(const double x)
{
if (x==0)
    return 1;
return sin(x)/x;
}


static QVector<qreal> firstControlPoints(const QVector<qreal>& vector)
{
    QVector<qreal> result;

    int count = vector.count();
    result.resize(count);
    result[0] = vector[0] / 2.0;

    QVector<qreal> temp;
    temp.resize(count);
    temp[0] = 0;

    qreal b = 2.0;

    for (int i = 1; i < count; i++) {
        temp[i] = 1 / b;
        b = (i < count - 1 ? 4.0 : 3.5) - temp[i];
        result[i] = (vector[i] - result[i - 1]) / b;
    }

    for (int i = 1; i < count; i++)
        result[count - i - 1] -= temp[count - i] * result[count - i];

    return result;
}

/*!
  Calculates control points which are needed by QPainterPath.cubicTo function to draw the cubic Bezier cureve between two points.
*/
static QVector<QPointF> calculateControlPoints(const QVector<QPointF> &points)
{
    QVector<QPointF> controlPoints;
    controlPoints.resize(points.count() * 2 - 2);

    int n = points.count() - 1;

    if (n == 1) {
        //for n==1
        controlPoints[0].setX((2 * points[0].x() + points[1].x()) / 3);
        controlPoints[0].setY((2 * points[0].y() + points[1].y()) / 3);
        controlPoints[1].setX(2 * controlPoints[0].x() - points[0].x());
        controlPoints[1].setY(2 * controlPoints[0].y() - points[0].y());
        return controlPoints;
    }

    // Calculate first Bezier control points
    // Set of equations for P0 to Pn points.
    //
    //  |   2   1   0   0   ... 0   0   0   ... 0   0   0   |   |   P1_1    |   |   P0 + 2 * P1             |
    //  |   1   4   1   0   ... 0   0   0   ... 0   0   0   |   |   P1_2    |   |   4 * P1 + 2 * P2         |
    //  |   0   1   4   1   ... 0   0   0   ... 0   0   0   |   |   P1_3    |   |   4 * P2 + 2 * P3         |
    //  |   .   .   .   .   .   .   .   .   .   .   .   .   |   |   ...     |   |   ...                     |
    //  |   0   0   0   0   ... 1   4   1   ... 0   0   0   | * |   P1_i    | = |   4 * P(i-1) + 2 * Pi     |
    //  |   .   .   .   .   .   .   .   .   .   .   .   .   |   |   ...     |   |   ...                     |
    //  |   0   0   0   0   0   0   0   0   ... 1   4   1   |   |   P1_(n-1)|   |   4 * P(n-2) + 2 * P(n-1) |
    //  |   0   0   0   0   0   0   0   0   ... 0   2   7   |   |   P1_n    |   |   8 * P(n-1) + Pn         |
    //
    QVector<qreal> vector;
    vector.resize(n);

    vector[0] = points[0].x() + 2 * points[1].x();


    for (int i = 1; i < n - 1; ++i)
        vector[i] = 4 * points[i].x() + 2 * points[i + 1].x();

    vector[n - 1] = (8 * points[n - 1].x() + points[n].x()) / 2.0;

    QVector<qreal> xControl = firstControlPoints(vector);

    vector[0] = points[0].y() + 2 * points[1].y();

    for (int i = 1; i < n - 1; ++i)
        vector[i] = 4 * points[i].y() + 2 * points[i + 1].y();

    vector[n - 1] = (8 * points[n - 1].y() + points[n].y()) / 2.0;

    QVector<qreal> yControl = firstControlPoints(vector);

    for (int i = 0, j = 0; i < n; ++i, ++j) {

        controlPoints[j].setX(xControl[i]);
        controlPoints[j].setY(yControl[i]);

        j++;

        if (i < n - 1) {
            controlPoints[j].setX(2 * points[i + 1].x() - xControl[i + 1]);
            controlPoints[j].setY(2 * points[i + 1].y() - yControl[i + 1]);
        } else {
            controlPoints[j].setX((points[n].x() + xControl[n - 1]) / 2);
            controlPoints[j].setY((points[n].y() + yControl[n - 1]) / 2);
        }
    }
    return controlPoints;
}



QPainterPath splineFromPoints(const QVector<QPointF> &points, int penWidth)
{
    QPainterPath splinePath;
    QVector<QPointF> controlPoints;
    if (points.count() >= 2)
        controlPoints = calculateControlPoints(points);

    if ((points.size() < 2) || (controlPoints.size() < 2)) {
        return splinePath;
    }

    Q_ASSERT(points.count() * 2 - 2 == controlPoints.count());

    // Use worst case scenario to determine required margin.
    qreal margin = penWidth * 1.42;

    splinePath.moveTo(points.at(0));
    for (int i = 0; i < points.size() - 1; i++) {
        const QPointF &point = points.at(i + 1);
        splinePath.cubicTo(controlPoints[2 * i], controlPoints[2 * i + 1], point);
    }
    return splinePath;
}
