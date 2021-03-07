/*
 * CTU/EMBO - EMBedded Oscilloscope <github.com/parezj/EMBO>
 * Author: Jakub Parez <parez.jakub@gmail.com>
 */

#ifndef CUSTOMDIAL_H
#define CUSTOMDIAL_H

#include <QDial>

#define DEFAULT_PIXMAP ":/main/resources/img/power-off-gray.png"

class QCustomDial : public QDial
{
    Q_OBJECT

    Q_PROPERTY(QPixmap backgroundImage READ backgroundImage WRITE setBackgroundImage DESIGNABLE true)

 public:
    explicit QCustomDial(QWidget* parent = nullptr);
    ~QCustomDial();

    QPixmap backgroundImage() { return *m_bg; }

    void setBackgroundImage(QPixmap pixmap)
    {
        *m_bg = pixmap;
        update();
    }

 private:
    virtual void paintEvent(QPaintEvent*) override;

    QPixmap* m_bg = Q_NULLPTR;
    QPixmap* m_bg_default = new QPixmap(DEFAULT_PIXMAP);
};


#endif // CUSTOMDIAL_H
