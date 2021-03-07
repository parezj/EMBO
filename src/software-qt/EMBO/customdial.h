#ifndef CUSTOMDIAL_HPP
#define CUSTOMDIAL_HPP

#include <QDial>
#include <QString>
#include <QSharedPointer>
#include <QRectF>
#include <QPen>
#include <QColor>

class QColor;
class QRectF;
class QPen;

class CustomDial : public QDial
{
    Q_OBJECT

    Q_PROPERTY(QString arcColor READ getArcColor WRITE setArcColor)

    Q_PROPERTY(double arcWidth READ getArcWidth WRITE setArcWidth)

public:

    explicit CustomDial(QWidget* parent = nullptr);
    ~CustomDial();

    CustomDial(const QString& text,
               QWidget * parent = nullptr,
               int minimum = 0,
               int maximum = 999);


    void setArcColor(const QString& color);

    QString getArcColor() const;


    void setStartAngle(double angle);

    double getStartAngle() const;


    void setMaximumAngle(double angle);

    double getMaximumAngle() const;


    void setArcWidth(double px);

    double getArcWidth() const;


    void setText(const QString& text);

    QString getText() const;


private slots:

    void updateValue();

private:

    virtual void paintEvent(QPaintEvent*) override;

    virtual void resizeEvent(QResizeEvent* event) override;

    double maximumAngleSpan_;

    double startAngle_;

    double arcWidth_;

    double angleSpan_;

    QString valueString_;

    QString text_;

    QSharedPointer<QRectF> arcRect_ = QSharedPointer<QRectF>(new QRectF);

    QSharedPointer<QRectF> valueRect_ = QSharedPointer<QRectF>(new QRectF);

    QSharedPointer<QRectF> textRect_ = QSharedPointer<QRectF>(new QRectF);

    QSharedPointer<QColor> arcColor_ = QSharedPointer<QColor>(new QColor);

    QSharedPointer<QPen> arcPen_ = QSharedPointer<QPen>(new QPen);
};

#endif // CUSTOMDIAL_HPP
