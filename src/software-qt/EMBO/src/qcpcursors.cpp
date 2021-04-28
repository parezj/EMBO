/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "qcpcursors.h"
#include "css.h"


/* classic mode */

#define PERCENT_MAX         1000.0

#define HCUROSR_DIFF_POS    850.0
#define VCUROSR_DIFF_POS    170.0
#define HCUROSR_DIFF_POS2   850.0
#define VCUROSR_DIFF_POS2   200.0

#define CURSOR_DIFF_CNTR    500.0

/* single cursor mode */

#define PERCENT_MAX3        100.0

#define CURSOR_DIFF_CNTR3   50.0
#define HCUROSR_DIFF_POS3   90.0
#define VCUROSR_DIFF_POS3   10.0

int QCPCursors::uniqueNum = 0;


QCPCursors::QCPCursors(QObject* parent, QCustomPlot* plot, QCPAxisRect* rect, bool center,
                       QColor colorH, QColor colorV, QColor colorDiff, QColor colorText) : QObject(parent)
{
    m_center = center;
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

    m_textH_min = new QCPItemText(m_plot);
    m_textH_max = new QCPItemText(m_plot);
    m_textH_diff = new QCPItemText(m_plot);
    m_textH_diff2 = new QCPItemText(m_plot);

    m_textV_min = new QCPItemText(m_plot);
    m_textV_max = new QCPItemText(m_plot);
    m_textV_diff = new QCPItemText(m_plot);

    if (rect != NULL)
    {        
        m_cursorH_min->setClipAxisRect(rect);
        m_cursorH_max->setClipAxisRect(rect);
        m_cursorH_diff->setClipAxisRect(rect);

        m_cursorV_min->setClipAxisRect(rect);
        m_cursorV_max->setClipAxisRect(rect);
        m_cursorV_diff->setClipAxisRect(rect);

        m_textH_min->setClipAxisRect(rect);
        m_textH_max->setClipAxisRect(rect);
        m_textH_diff->setClipAxisRect(rect);
        m_textH_diff2->setClipAxisRect(rect);

        m_textV_min->setClipAxisRect(rect);
        m_textV_diff->setClipAxisRect(rect);
        m_textV_diff->setClipAxisRect(rect);                

        m_cursorH_min->start->setType(QCPItemPosition::ptPlotCoords);
        m_cursorH_min->start->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_cursorH_min->end->setType(QCPItemPosition::ptPlotCoords);
        m_cursorH_min->end->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_cursorH_max->start->setType(QCPItemPosition::ptPlotCoords);
        m_cursorH_max->start->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_cursorH_max->end->setType(QCPItemPosition::ptPlotCoords);
        m_cursorH_max->end->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_cursorH_diff->start->setType(QCPItemPosition::ptPlotCoords);
        m_cursorH_diff->start->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));;
        m_cursorH_diff->end->setType(QCPItemPosition::ptPlotCoords);
        m_cursorH_diff->end->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));

        m_cursorV_min->start->setType(QCPItemPosition::ptPlotCoords);
        m_cursorV_min->start->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_cursorV_min->end->setType(QCPItemPosition::ptPlotCoords);
        m_cursorV_min->end->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_cursorV_max->start->setType(QCPItemPosition::ptPlotCoords);
        m_cursorV_max->start->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_cursorV_max->end->setType(QCPItemPosition::ptPlotCoords);
        m_cursorV_max->end->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_cursorV_diff->start->setType(QCPItemPosition::ptPlotCoords);
        m_cursorV_diff->start->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));;
        m_cursorV_diff->end->setType(QCPItemPosition::ptPlotCoords);
        m_cursorV_diff->end->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));

        m_textH_min->position->setType(QCPItemPosition::ptPlotCoords);
        m_textH_min->position->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_textH_max->position->setType(QCPItemPosition::ptPlotCoords);
        m_textH_max->position->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_textH_diff->position->setType(QCPItemPosition::ptPlotCoords);
        m_textH_diff->position->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_textH_diff2->position->setType(QCPItemPosition::ptPlotCoords);
        m_textH_diff2->position->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));

        m_textV_min->position->setType(QCPItemPosition::ptPlotCoords);
        m_textV_min->position->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_textV_diff->position->setType(QCPItemPosition::ptPlotCoords);
        m_textV_diff->position->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
        m_textV_diff->position->setType(QCPItemPosition::ptPlotCoords);
        m_textV_diff->position->setAxes(rect->axis(QCPAxis::atBottom), rect->axis(QCPAxis::atLeft));
    }

    m_cursorH_min->setLayer(m_cursorsLayerH);
    m_cursorH_max->setLayer(m_cursorsLayerH);
    m_cursorH_diff->setLayer(m_cursorsLayerH);

    m_cursorV_min->setLayer(m_cursorsLayerV);
    m_cursorV_max->setLayer(m_cursorsLayerV);
    m_cursorV_diff->setLayer(m_cursorsLayerV);

    m_textH_min->setLayer(m_cursorsLayerH);
    m_textH_max->setLayer(m_cursorsLayerH);
    m_textH_diff->setLayer(m_cursorsLayerH);
    m_textH_diff2->setLayer(m_cursorsLayerH);

    m_textV_min->setLayer(m_cursorsLayerV);
    m_textV_max->setLayer(m_cursorsLayerV);
    m_textV_diff->setLayer(m_cursorsLayerV);

    QFont font1("Roboto", 12, QFont::Normal);
    m_textH_min->setFont(font1);
    m_textH_max->setFont(font1);
    m_textH_diff->setFont(font1);

    QFont font2("Roboto", 10, QFont::Normal);
    m_textH_diff2->setFont(font2);

    m_textV_min->setFont(font1);
    m_textV_max->setFont(font1);
    m_textV_diff->setFont(font1);

    m_textH_min->setColor(colorText);
    m_textH_max->setColor(colorText);
    m_textH_diff->setColor(colorText);
    m_textH_diff2->setColor(colorText);

    m_textH_min->setBrush(QColor(255,255,255,200));
    m_textH_max->setBrush(QColor(255,255,255,200));
    m_textH_diff->setBrush(QColor(255,255,255,200));
    m_textH_diff2->setBrush(QColor(255,255,255,200));

    m_textV_min->setColor(colorText);
    m_textV_max->setColor(colorText);
    m_textV_diff->setColor(colorText);

    m_textV_min->setBrush(QColor(255,255,255,200));
    m_textV_max->setBrush(QColor(255,255,255,200));
    m_textV_diff->setBrush(QColor(255,255,255,200));

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

    reCalcH();

    m_cursorsLayerH->replot();
}

void QCPCursors::setH_max(int percent, double hRangeMin, double hRangeMax)
{
    m_hMaxVal = percent;
    m_hRangeMin = hRangeMin;
    m_hRangeMax = hRangeMax;

    reCalcH();

    m_cursorsLayerH->replot();
}

void QCPCursors::setV_min(int percent, double vRangeMin, double vRangeMax)
{
    m_vMinVal = percent;
    m_vRangeMin = vRangeMin;
    m_vRangeMax = vRangeMax;

    reCalcV();

    m_cursorsLayerV->replot();
}

void QCPCursors::setV_max(int percent, double vRangeMin, double vRangeMax)
{
    m_vMaxVal = percent;
    m_vRangeMin = vRangeMin;
    m_vRangeMax = vRangeMax;

    reCalcV();

    m_cursorsLayerV->replot();
}

void QCPCursors::refresh(double vRangeMin, double vRangeMax, double hRangeMin, double hRangeMax, bool replot)
{
    m_vRangeMin = vRangeMin;
    m_vRangeMax = vRangeMax;
    m_hRangeMin = hRangeMin;
    m_hRangeMax = hRangeMax;

    reCalcH();
    reCalcV();

    if (replot)
    {
        m_cursorsLayerV->replot();
        m_cursorsLayerH->replot();
    }
}

void QCPCursors::showH(bool val)
{
    m_cursorsLayerH->setVisible(val);
    m_cursorsLayerH->replot();
}

void QCPCursors::showV(bool val)
{
    m_cursorsLayerV->setVisible(val);
    m_cursorsLayerV->replot();
}

void QCPCursors::reCalcH()
{
    double dH = m_hRangeMax - m_hRangeMin;
    double dV = m_vRangeMax - m_vRangeMin;

    double valHmax = ((double)(m_hMaxVal / PERCENT_MAX) * dH) + m_hRangeMin;
    double valHmin = ((double)(m_hMinVal / PERCENT_MAX) * dH) + m_hRangeMin;

    m_cursorH_min->start->setCoords(valHmin, -QCPRange::maxRange);
    m_cursorH_min->end->setCoords(valHmin, QCPRange::maxRange);

    m_cursorH_max->start->setCoords(valHmax, -QCPRange::maxRange);
    m_cursorH_max->end->setCoords(valHmax, QCPRange::maxRange);

    double valHdiff = valHmax - valHmin;

    m_textH_min->setText(' ' + QCPCursors::formatUnitS(valHmin) + ' ');
    m_textH_max->setText(' ' + QCPCursors::formatUnitS(valHmax) + ' ');
    m_textH_diff->setText(" Δ " + QCPCursors::formatUnitS(valHdiff) + ' ');
    m_textH_diff2->setText(" Δ " + QCPCursors::formatUnitHz(1/valHdiff) + ' ');

    double valHdiffPos = ((double)((m_center ? CURSOR_DIFF_CNTR : HCUROSR_DIFF_POS) / PERCENT_MAX) * dV) + m_vRangeMin;
    double valHminMaxPos = ((double)((m_center ? CURSOR_DIFF_CNTR : HCUROSR_DIFF_POS2) / PERCENT_MAX) * dV) + m_vRangeMin;

    double m_textH_min_sz = m_textH_min->bottomRight->pixelPosition().x() - m_textH_min->bottomLeft->pixelPosition().x();
    double m_textH_max_sz = m_textH_max->bottomRight->pixelPosition().x() - m_textH_max->bottomLeft->pixelPosition().x();

    m_cursorH_diff->start->setCoords(valHmin, valHdiffPos);
    m_cursorH_diff->end->setCoords(valHmax, valHdiffPos);

    m_textH_min->position->setCoords(QPointF(valHmin, valHminMaxPos));
    m_textH_min->position->setPixelPosition(m_textH_min->position->pixelPosition() + QPointF(-(m_textH_min_sz / 2) - 10, 20.0));

    m_textH_max->position->setCoords(QPointF(valHmax, valHminMaxPos));
    m_textH_max->position->setPixelPosition(m_textH_max->position->pixelPosition() + QPointF((m_textH_max_sz / 2) + 10, 20.0));

    m_textH_diff->position->setCoords(QPointF(((valHmax - valHmin) / 2.0) + valHmin, valHdiffPos));
    m_textH_diff->position->setPixelPosition(m_textH_diff->position->pixelPosition() + QPointF(0, -20.0));

    m_textH_diff2->position->setCoords(QPointF(((valHmax - valHmin) / 2.0) + valHmin, valHdiffPos));
    m_textH_diff2->position->setPixelPosition(m_textH_diff->position->pixelPosition() + QPointF(0, -20.0));
}

void QCPCursors::reCalcV()
{
    double dH = m_hRangeMax - m_hRangeMin;
    double dV = m_vRangeMax - m_vRangeMin;

    double valVmax = ((double)(m_vMaxVal / PERCENT_MAX) * dV) + m_vRangeMin;
    double valVmin = ((double)(m_vMinVal / PERCENT_MAX) * dV) + m_vRangeMin;

    m_cursorV_min->start->setCoords(-QCPRange::maxRange, valVmin);
    m_cursorV_min->end->setCoords(QCPRange::maxRange, valVmin);

    m_cursorV_max->start->setCoords(-QCPRange::maxRange, valVmax);
    m_cursorV_max->end->setCoords(QCPRange::maxRange, valVmax);

    double valVdiff = valVmax - valVmin;

    m_textV_min->setText(' ' + QCPCursors::formatUnitV(valVmin) + ' ');
    m_textV_max->setText(' ' + QCPCursors::formatUnitV(valVmax) + ' ');
    m_textV_diff->setText(" Δ " + QCPCursors::formatUnitV(valVdiff) + ' ');

    double valVdiffPos = ((double)((m_center ? CURSOR_DIFF_CNTR : VCUROSR_DIFF_POS) / PERCENT_MAX) * dH) + m_hRangeMin;
    double valVminMaxPos = ((double)((m_center ? CURSOR_DIFF_CNTR : VCUROSR_DIFF_POS2) / PERCENT_MAX) * dH) + m_hRangeMin;

    double m_textV_min_sz = m_textV_min->bottomRight->pixelPosition().x() - m_textV_min->bottomLeft->pixelPosition().x();
    double m_textV_max_sz = m_textV_max->bottomRight->pixelPosition().x() - m_textV_max->bottomLeft->pixelPosition().x();
    double m_textV_diff_sz = m_textV_diff->bottomRight->pixelPosition().x() - m_textV_diff->bottomLeft->pixelPosition().x();

    m_cursorV_diff->start->setCoords(valVdiffPos, valVmin);
    m_cursorV_diff->end->setCoords(valVdiffPos, valVmax);

    m_textV_min->position->setCoords(QPointF(valVminMaxPos, valVmin));
    m_textV_min->position->setPixelPosition(m_textV_min->position->pixelPosition() + QPointF((m_textV_min_sz / 2), 15.0));

    m_textV_max->position->setCoords(QPointF(valVminMaxPos, valVmax));
    m_textV_max->position->setPixelPosition(m_textV_max->position->pixelPosition() + QPointF((m_textV_max_sz / 2), -15.0));

    m_textV_diff->position->setCoords(QPointF(valVdiffPos, ((valVmax - valVmin) / 2.0) + valVmin));
    m_textV_diff->position->setPixelPosition(m_textV_diff->position->pixelPosition() + QPointF(-(m_textV_diff_sz / 2) - 10, 0));
}

const QString QCPCursors::formatUnitV(double value)
{
    const char unit = 'V';

    if (value == 0)
        return "0 V";
    else if (value < 1)
        return(QString::number(value * 1000, 'd', 1) + " m" + unit);
    else // if (value < 1000)
        return(QString::number(value * 1, 'd', 3) + " " + unit);
}

const QString QCPCursors::formatUnitHz(double value)
{
    const QString unit = "Hz";

    if (value == 0)
        return "0 Hz";
    else if (value < 1000)
        return(QString::number(value * 1, 'd', 3).left(5) + " " + unit);
    else if (value < 1000000)
        return(QString::number(value * 0.001, 'd', 3).left(5) + " k" + unit);
    else if (value < 1000000000)
        return(QString::number(value * 0.000001, 'd', 3).left(5) + " M" + unit);
    else if (value < 1000000000000)
        return(QString::number(value * 0.000000001, 'd', 3).left(5) + " G" + unit);
    else // if (value < 1000000000000)
        return(QString::number(value * 0.000000001, 'd', 3).left(5) + " " + unit);
}

const QString QCPCursors::formatUnitS(double value)
{
    const char unit = 's';
    double abs = value;
    if (abs < 0)
        abs *= -1;

    if (abs < 0.000000001)
        return "0 s";
    else if (abs < 0.000001)
        return(QString::number(value * 1000000000, 'd', 3).left(5) + " n" + unit);
    else if (abs < 0.001)
        return(QString::number(value * 1000000, 'd', 3).left(5) + " u" + unit);
    else if (abs < 1)
        return(QString::number(value * 1000, 'd', 3).left(5) + " m" + unit);
    else if (abs < 1000)
        return(QString::number(value * 1, 'd', 3).left(6) + " " + unit);
    else // if (value < 1000000)
        return(QString::number(value * 1, 'd', 1) + " " + unit);
}

void QCPCursors::showText(bool val)
{
    m_textH_min->setVisible(val);
    m_textH_max->setVisible(val);
    m_textH_diff->setVisible(val);
    m_textH_diff2->setVisible(val);

    m_textV_min->setVisible(val);
    m_textV_max->setVisible(val);
    m_textV_diff->setVisible(val);

    m_cursorV_diff->setVisible(val);
    m_cursorH_diff->setVisible(val);
}

/* single cursor */

QCPCursor::QCPCursor(QObject* parent, QCustomPlot* plot, QCPAxisRect* rect, bool horizontal, bool center,
                     QColor colorLine, QColor colorText, Qt::PenStyle style) : QObject(parent)
{
    m_center = center;
    m_plot = plot;
    m_horizontal = horizontal;

    QString layerName = "cursorLayer" + QString::number(QCPCursors::getUniqueNum());

    m_plot->addLayer(layerName, 0, QCustomPlot::limAbove);

    m_cursorLayer = plot->layer(layerName);
    m_cursorLayer->setMode(QCPLayer::lmBuffered);

    m_cursor = new QCPItemLine(m_plot);
    m_cursor->setLayer(m_cursorLayer);

    m_text = new QCPItemText(m_plot);
    m_text->setLayer(m_cursorLayer);

    if (rect != NULL)
    {
        m_cursor->setClipAxisRect(rect);
        m_text->setClipAxisRect(rect);

        m_cursor->setClipToAxisRect(true);
        m_text->setClipToAxisRect(true);
    }

    m_cursor->setPen(QPen(colorLine, 1, style, Qt::RoundCap, Qt::RoundJoin));

    QFont font1("Roboto", 12, QFont::Normal);
    m_text->setFont(font1);
    m_text->setColor(colorText);
    m_text->setBrush(QColor(255,255,255,200));

    m_cursorLayer->setVisible(false);
}

void QCPCursor::setValue(int percent, double vRangeMin, double vRangeMax, double hRangeMin, double hRangeMax)
{
    m_value = percent;

    m_vRangeMin = vRangeMin;
    m_vRangeMax = vRangeMax;
    m_hRangeMin = hRangeMin;
    m_hRangeMax = hRangeMax;

    reCalc();

    m_cursorLayer->replot();
}

void QCPCursor::refresh(double vRangeMin, double vRangeMax, double hRangeMin, double hRangeMax, bool replot)
{
    m_vRangeMin = vRangeMin;
    m_vRangeMax = vRangeMax;
    m_hRangeMin = hRangeMin;
    m_hRangeMax = hRangeMax;

    reCalc();

    if (replot)
        m_cursorLayer->replot();
}

void QCPCursor::show(bool val)
{
    m_cursorLayer->setVisible(val);
    m_cursorLayer->replot();
}

void QCPCursor::reCalc()
{
    double dH = m_hRangeMax - m_hRangeMin;
    double dV = m_vRangeMax - m_vRangeMin;

    double val = ((double)(m_value / PERCENT_MAX3) * (m_horizontal ? dV : dH)) + (m_horizontal ? m_vRangeMin : m_hRangeMin);

    double textPos = ((double)((m_center ? CURSOR_DIFF_CNTR3 : (m_horizontal ? HCUROSR_DIFF_POS3 : VCUROSR_DIFF_POS3)) / PERCENT_MAX3) *
                      (m_horizontal ? dH : dV)) + (m_horizontal ? m_hRangeMin : m_vRangeMin);

    double m_text_sz = m_text->bottomRight->pixelPosition().x() - m_text->bottomLeft->pixelPosition().x();

    if (!m_horizontal)
    {
        m_text->setText(' ' + QCPCursors::formatUnitS(val) + ' ');

        m_text->position->setCoords(QPointF(val, textPos));
        m_text->position->setPixelPosition(m_text->position->pixelPosition() + QPointF(-(m_text_sz / 2) - 10, 0));

        m_cursor->start->setCoords(val, -QCPRange::maxRange);
        m_cursor->end->setCoords(val, QCPRange::maxRange);
    }
    else
    {
        m_text->setText(' ' + QCPCursors::formatUnitV(val) + ' ');

        m_text->position->setCoords(QPointF(textPos, val));
        m_text->position->setPixelPosition(m_text->position->pixelPosition() + QPointF(0, 10.0));

        m_cursor->start->setCoords(-QCPRange::maxRange, val);
        m_cursor->end->setCoords(QCPRange::maxRange, val);
    }
}

void QCPCursor::showText(bool val)
{
    m_text->setVisible(val);
}
