/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "qcpcursors.h"
#include "css.h"

#define PERCENT_MAX         1000.0
#define HCUROSR_DIFF_POS    900.0
#define VCUROSR_DIFF_POS    100.0

int QCPCursors::uniqueNum = 0;


QCPCursors::QCPCursors(QObject* parent, QCustomPlot* plot,
                       QColor colorH, QColor colorV, QColor colorDiff, QColor colorText) : QObject(parent)
{
    m_plot = plot;

    QString layerNameH = "cursorsLayerH" + QString::number(QCPCursors::getUniqueNum());
    QString layerNameV = "cursorsLayerV" + QString::number(QCPCursors::getUniqueNum());

    plot->addLayer(layerNameH, 0, QCustomPlot::limAbove);
    plot->addLayer(layerNameV, 0, QCustomPlot::limAbove);

    m_cursorsLayerH = plot->layer(layerNameH);
    m_cursorsLayerV = plot->layer(layerNameV);

    m_cursorsLayerH->setMode(QCPLayer::lmBuffered);
    m_cursorsLayerV->setMode(QCPLayer::lmBuffered);

    m_cursorH_min = new QCPItemLine(m_plot);
    m_cursorH_max = new QCPItemLine(m_plot);
    m_cursorH_diff = new QCPItemLine(m_plot);

    m_cursorV_min = new QCPItemLine(m_plot);
    m_cursorV_max = new QCPItemLine(m_plot);
    m_cursorV_diff = new QCPItemLine(m_plot);

    m_textH_min= new QCPItemText(m_plot);
    m_textH_max = new QCPItemText(m_plot);
    m_textH_diff = new QCPItemText(m_plot);

    m_textV_min= new QCPItemText(m_plot);
    m_textV_max = new QCPItemText(m_plot);
    m_textV_diff = new QCPItemText(m_plot);

    m_cursorH_min->setLayer(m_cursorsLayerH);
    m_cursorH_max->setLayer(m_cursorsLayerH);
    m_cursorH_diff->setLayer(m_cursorsLayerH);

    m_cursorV_min->setLayer(m_cursorsLayerV);
    m_cursorV_max->setLayer(m_cursorsLayerV);
    m_cursorV_diff->setLayer(m_cursorsLayerV);

    m_textH_min->setLayer(m_cursorsLayerH);
    m_textH_max->setLayer(m_cursorsLayerH);
    m_textH_diff->setLayer(m_cursorsLayerH);

    m_textV_min->setLayer(m_cursorsLayerV);
    m_textV_max->setLayer(m_cursorsLayerV);
    m_textV_diff->setLayer(m_cursorsLayerV);

    QFont font1("Roboto", 12, QFont::Normal);
    m_textH_min->setFont(font1);
    m_textH_max->setFont(font1);
    m_textH_diff->setFont(font1);

    m_textV_min->setFont(font1);
    m_textV_max->setFont(font1);
    m_textV_diff->setFont(font1);

    m_textH_min->setColor(colorText);
    m_textH_max->setColor(colorText);
    m_textH_diff->setColor(colorText);

    m_textV_min->setColor(colorText);
    m_textV_max->setColor(colorText);
    m_textV_diff->setColor(colorText);

    m_cursorH_min->setPen(QPen(colorH, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    m_cursorH_max->setPen(QPen(colorH, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    m_cursorV_min->setPen(QPen(colorV, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    m_cursorV_max->setPen(QPen(colorV, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

    m_cursorH_diff->setPen(QPen(colorDiff, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));
    m_cursorV_diff->setPen(QPen(colorDiff, 1, Qt::DashLine, Qt::RoundCap, Qt::RoundJoin));

    m_cursorH_diff->setTail(QCPLineEnding::esFlatArrow);
    m_cursorH_diff->setHead(QCPLineEnding::esFlatArrow);

    m_cursorV_diff->setTail(QCPLineEnding::esFlatArrow);
    m_cursorV_diff->setHead(QCPLineEnding::esFlatArrow);

    m_cursorsLayerH->setVisible(false);
    m_cursorsLayerV->setVisible(false);
}

void QCPCursors::setH_min(int percent, double hRangeMin, double hRangeMax)
{
    m_hMinVal = percent;
    m_hRangeMin = hRangeMin;
    m_hRangeMax = hRangeMax;

    reCalc();

    m_cursorsLayerH->replot();
}

void QCPCursors::setH_max(int percent, double hRangeMin, double hRangeMax)
{
    m_hMaxVal = percent;
    m_hRangeMin = hRangeMin;
    m_hRangeMax = hRangeMax;

    reCalc();

    m_cursorsLayerH->replot();
}

void QCPCursors::setV_min(int percent, double vRangeMin, double vRangeMax)
{
    m_vMinVal = percent;
    m_vRangeMin = vRangeMin;
    m_vRangeMax = vRangeMax;

    reCalc();

    m_cursorsLayerV->replot();
}

void QCPCursors::setV_max(int percent, double vRangeMin, double vRangeMax)
{
    m_vMaxVal = percent;
    m_vRangeMin = vRangeMin;
    m_vRangeMax = vRangeMax;

    reCalc();

    m_cursorsLayerV->replot();
}

void QCPCursors::refresh(double vRangeMin, double vRangeMax, double hRangeMin, double hRangeMax, bool replot)
{
    m_vRangeMin = vRangeMin;
    m_vRangeMax = vRangeMax;
    m_hRangeMin = hRangeMin;
    m_hRangeMax = hRangeMax;

    reCalc();

    if (replot)
    {
        m_cursorsLayerV->replot();
        m_cursorsLayerH->replot();
    }
}

void QCPCursors::showH(bool val)
{
    m_cursorsLayerH->setVisible(val);
}

void QCPCursors::showV(bool val)
{
    m_cursorsLayerV->setVisible(val);
}

void QCPCursors::reCalc()
{
    double dH = m_hRangeMax - m_hRangeMin;
    double dV = m_vRangeMax - m_vRangeMin;

    qInfo() << "dH:" << dH;
    qInfo() << "dV:" << dV;

    double valHmax = ((double)(m_hMaxVal / PERCENT_MAX) * dH) + m_hRangeMin;
    double valHmin = ((double)(m_hMinVal / PERCENT_MAX) * dH) + m_hRangeMin;
    double valVmax = ((double)(m_vMaxVal / PERCENT_MAX) * dV) + m_vRangeMin;
    double valVmin = ((double)(m_vMinVal / PERCENT_MAX) * dV) + m_vRangeMin;

    m_cursorH_min->start->setCoords(valHmin, -QCPRange::maxRange);
    m_cursorH_min->end->setCoords(valHmin, QCPRange::maxRange);

    m_cursorH_max->start->setCoords(valHmax, -QCPRange::maxRange);
    m_cursorH_max->end->setCoords(valHmax, QCPRange::maxRange);

    m_cursorV_min->start->setCoords(-QCPRange::maxRange, valVmin);
    m_cursorV_min->end->setCoords(QCPRange::maxRange, valVmin);

    m_cursorV_max->start->setCoords(-QCPRange::maxRange, valVmax);
    m_cursorV_max->end->setCoords(QCPRange::maxRange, valVmax);

    double valHdiff = ((double)(HCUROSR_DIFF_POS / PERCENT_MAX) * dV) + m_vRangeMin;
    double valVdiff = ((double)(VCUROSR_DIFF_POS / PERCENT_MAX) * dH) + m_hRangeMin;

    qInfo() << "HDIF:" << valHdiff;
    qInfo() << "VDIF:" << valVdiff;

    qInfo() << "hMin:" << valHmin;
    qInfo() << "hMax:" << valHmax;
    qInfo() << "vMin:" << valVmin;
    qInfo() << "vMax:" << valVmax;

    m_cursorH_diff->start->setCoords(valHmin, valHdiff);
    m_cursorH_diff->end->setCoords(valHmax, valHdiff);

    m_cursorV_diff->start->setCoords(valVdiff, valVmin);
    m_cursorV_diff->end->setCoords(valVdiff, valVmax);

    const double margin_diff = 10;

    m_textH_min->position->setCoords(QPointF(valHmin, valHdiff));
    m_textH_min->position->setPixelPosition(m_textH_min->position->pixelPosition() + QPointF(10.0, margin_diff));

    m_textH_max->position->setCoords(QPointF(valHmax, valHdiff));
    m_textH_max->position->setPixelPosition(m_textH_max->position->pixelPosition() + QPointF(-10.0, margin_diff));

    m_textH_diff->position->setCoords(QPointF(((valHmax - valHmin) / 2.0) + valHmin, valHdiff));
    m_textH_diff->position->setPixelPosition(m_textH_diff->position->pixelPosition() + QPointF(0, margin_diff));

    m_textV_min->position->setCoords(QPointF(valVdiff, valVmin));
    m_textV_min->position->setPixelPosition(m_textV_min->position->pixelPosition() + QPointF(margin_diff, 10.0));

    m_textV_max->position->setCoords(QPointF(valVdiff, valVmax));
    m_textV_max->position->setPixelPosition(m_textV_max->position->pixelPosition() + QPointF(margin_diff, -10.0));

    m_textV_diff->position->setCoords(QPointF(valVdiff, ((valVmax - valVmin) / 2.0) + valVmin));
    m_textV_diff->position->setPixelPosition(m_textV_diff->position->pixelPosition() + QPointF(margin_diff, 0));

    QString valHmin_s;
    QString valHmax_s;
    QString valHdiff_s;

    QString valVmin_s;
    QString valVmax_s;
    QString valVdiff_s;

    valHmin_s = valHmin_s.asprintf("%.3f", valHmin);
    valHmax_s = valHmin_s.asprintf("%.3f", valHmax);
    valHdiff_s = valHmin_s.asprintf("%.3f", valHmax - valHmin);

    valVmin_s = valVmin_s.asprintf("%.3f", valVmin);
    valVmax_s = valVmin_s.asprintf("%.3f", valVmax);
    valVdiff_s = valVmin_s.asprintf("%.3f", valVmax - valVmin);


    m_textH_min->setText(valHmin_s);
    m_textH_max->setText(valHmax_s);
    m_textH_diff->setText("Δ " + valHdiff_s);

    m_textV_min->setText(valVmin_s);
    m_textV_max->setText(valVmax_s);
    m_textV_diff->setText("Δ " + valVdiff_s);
}

/* single cursor */

QCPCursor::QCPCursor(QObject* parent, QCustomPlot* plot, bool horizontal,
                     QColor color, Qt::PenStyle style) : QObject(parent)
{
    m_plot = plot;
    m_horizontal = horizontal;

    QString layerName = "cursorLayer" + QString::number(QCPCursors::getUniqueNum());

    m_plot->addLayer(layerName, 0, QCustomPlot::limAbove);

    m_cursorLayer = plot->layer(layerName);
    m_cursorLayer->setMode(QCPLayer::lmBuffered);

    m_cursor = new QCPItemLine(m_plot);
    m_cursor->setLayer(m_cursorLayer);

    m_cursor->setPen(QPen(color, 1, style, Qt::RoundCap, Qt::RoundJoin));

    m_cursorLayer->setVisible(false);
}

void QCPCursor::setValue(int percent, double rangeMin, double rangeMax)
{
    m_value = percent;
    m_rangeMin = rangeMin;
    m_rangeMax = rangeMax;

    reCalc();

    m_cursorLayer->replot();
}

void QCPCursor::refresh(double rangeMin, double rangeMax, bool replot)
{
    m_rangeMin = rangeMin;
    m_rangeMax = rangeMax;

    reCalc();

    if (replot)
        m_cursorLayer->replot();
}

void QCPCursor::show(bool val)
{
    m_cursorLayer->setVisible(val);
}

void QCPCursor::reCalc()
{
    double d = m_rangeMax - m_rangeMin;
    double val = ((double)(m_value / PERCENT_MAX) * d) + m_rangeMin;

    if (m_horizontal)
    {
        m_cursor->start->setCoords(val, -QCPRange::maxRange);
        m_cursor->end->setCoords(val, QCPRange::maxRange);
    }
    else
    {
        m_cursor->start->setCoords(-QCPRange::maxRange, val);
        m_cursor->end->setCoords(QCPRange::maxRange, val);
    }
}
