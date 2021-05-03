#ifndef QDIAL2_H
#define QDIAL2_H

#include <QDial>

class QDial2 : public QDial{
    Q_OBJECT
public:
    QDial2(QWidget * parent = NULL) : QDial(parent)
    {
        connect(this, SIGNAL(actionTriggered(int)), this, SLOT(onAction(int)));
    }
protected slots:
    void onAction(int val);
};


#endif // QDIAL2_H
