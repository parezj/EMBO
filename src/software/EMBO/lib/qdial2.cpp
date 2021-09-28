#include "qdial2.h"

void QDial2::onAction(int val){
    if (val == QAbstractSlider::SliderMove)
    {
        if (value() == maximum() && sliderPosition() < (maximum() - minimum()) / 2) {
            this->setSliderPosition(maximum());
        } else if (value() == minimum() && sliderPosition() > (maximum() - minimum()) / 2){
            this->setSliderPosition(minimum());
        }
    }
}
