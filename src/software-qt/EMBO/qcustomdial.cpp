/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#include "qcustomdial.h"

#include <QDial>
#include <QPainter>


QCustomDial::QCustomDial(QWidget* parent) : QDial(parent)
{
}

void QCustomDial::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    QPoint start(0, 0);
    painter.setRenderHints(QPainter::Antialiasing); // | QPainter::SmoothPixmapTransform,1);
    //painter.scale(this->width(), this->height());

    painter.setBackgroundMode(Qt::OpaqueMode);
    painter.setBrush(Qt::darkCyan);
    painter.setPen(QPen(Qt::NoPen));
    painter.drawEllipse(QDial::rect());

    //painter.drawPixmap(start, m_bg == Q_NULLPTR ? *m_bg_default : *m_bg);
}

QCustomDial::~QCustomDial()
{
    if (m_bg != Q_NULLPTR)
        delete m_bg;

    if (m_bg_default != Q_NULLPTR)
        delete m_bg_default;
}
