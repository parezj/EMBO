#include "customdial.h"

#include <QPainter>
#include <QColor>
#include <QLabel>
#include <QRectF>
#include <QPen>
#include <QResizeEvent>

CustomDial::CustomDial(QWidget* parent)
: QDial(parent)
{ }

CustomDial::CustomDial(const QString& text,
                       QWidget* parent,
                       int minimum,
                       int maximum)
: QDial(parent),
  text_(text)
{
    QDial::setRange(minimum, maximum);

    QDial::setCursor(Qt::PointingHandCursor);

    connect(this, &QDial::valueChanged,
            this, &CustomDial::updateValue);

    setMinimumSize(100,100);

    setMaximumAngle(-360);

    setStartAngle(270);

    updateValue();
}

CustomDial::~CustomDial() = default;

void CustomDial::paintEvent(QPaintEvent*)
{
    QPainter painter(this);

    // So that we can use the background color
    // Otherwise the background is transparent
    painter.setBackgroundMode(Qt::OpaqueMode);

    // Smooth out the circle
    painter.setRenderHint(QPainter::Antialiasing);

    // Use background color
    painter.setBrush(painter.background());

    // Get current pen before resetting so we have
    // access to the color() method which returns the
    // color from the stylesheet
    QPen textPen = painter.pen();

    // No border
    painter.setPen(QPen(Qt::NoPen));

    // Draw background circle
    painter.drawEllipse(QDial::rect());

    painter.setPen(textPen);

    painter.drawText(*textRect_, Qt::AlignHCenter | Qt::AlignBottom, text_);

    painter.drawText(*valueRect_, Qt::AlignCenter, valueString_);

    painter.setPen(*arcPen_);

    painter.drawArc(*arcRect_, startAngle_, angleSpan_);

}

void CustomDial::resizeEvent(QResizeEvent* event)
{
    QDial::setMinimumSize(event->size());

    double width = QDial::width() - (2 * arcWidth_);

    double height = width / 2;

    *textRect_ = QRectF(arcWidth_, arcWidth_, width, height);

    *valueRect_ = QRectF(arcWidth_, height, width, height);

    *arcRect_ = QRectF(arcWidth_ / 2,
                       arcWidth_ / 2,
                       QDial::width() - arcWidth_,
                       QDial::height() - arcWidth_);
}

void CustomDial::updateValue()
{
    double value = QDial::value();

    // Get ratio between current value and maximum to calculate angle
    double ratio = value / QDial::maximum();

    angleSpan_ = maximumAngleSpan_ * ratio;

    valueString_ = QString::number(value);
}

void CustomDial::setArcWidth(double px)
{
    arcWidth_ = px;

    *arcRect_ = QRectF(arcWidth_ / 2,
                       arcWidth_ / 2,
                       QDial::width() - arcWidth_,
                       QDial::height() - arcWidth_);

    arcPen_->setWidth(arcWidth_);
}

void CustomDial::setText(const QString& text)
{
    text_ = text;
}

QString CustomDial::getText() const
{
    return text_;
}

double CustomDial::getArcWidth() const
{
    return arcWidth_;
}

void CustomDial::setMaximumAngle(double angle)
{
    maximumAngleSpan_ = angle * 16;
}

double CustomDial::getMaximumAngle() const
{
    return maximumAngleSpan_ / 16;
}

void CustomDial::setStartAngle(double angle)
{
    startAngle_ = angle * 16;
}

double CustomDial::getStartAngle() const
{
    return startAngle_ / 16;
}

void CustomDial::setArcColor(const QString& color)
{
    arcColor_->setNamedColor(color);

    arcPen_->setColor(*arcColor_);
}

QString CustomDial::getArcColor() const
{
    return arcColor_->name();
}
