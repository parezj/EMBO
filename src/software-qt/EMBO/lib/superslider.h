#pragma once

#include "qslider.h"
#include "qlabel.h"


/*
*  Super sick nasty awesome double handled slider!
*
*   @author Steve
*/
class SuperSliderHandle;

class SuperSlider: public QSlider
{
  Q_OBJECT
public:
  /** Constructor */
  SuperSlider(QWidget *parent = 0);

  /** Store the alternate handle for this slider*/
  SuperSliderHandle *alt_handle;

  /** Overridden mouse release event */
  void mouseReleaseEvent(QMouseEvent *event);

  /** Returns the slider value for the alternate handle */
  int alt_value();

  /** Convenience function for setting the value of the alternate handle */
  void alt_setValue(int value);

  /** Resets the alternate handle to the right side of the slider */
  void Reset();

  /** Used to update the position of the alternate handle through the use of an event filter */
  void alt_update();
signals:
  /** Constructor */
  void alt_valueChanged(int);
};

class SliderEventFilter : public QObject
{
public:
  /** Constructor */
  SliderEventFilter(SuperSlider *_grandParent)
  {grandParent = _grandParent;};

protected:
  /*
  * overloaded functions for object that inherit from this class
  */
  bool eventFilter(QObject* obj, QEvent* event);

private:
  /** Store the SuperSlider that this event filter is used within. */
  SuperSlider *grandParent;
};

class SuperSliderHandle: public QLabel
{
  Q_OBJECT
public:
  /** Constructor */
  SuperSliderHandle(SuperSlider *parent = 0);

  /** An overloaded mousePressevent so that we can start grabbing the cursor and using it's position for the value */
  void mousePressEvent(QMouseEvent *event);

  /** Returns the value of this handle with respect to the slider */
  int value();

  /** Maps mouse coordinates to slider values */
  int mapValue();

  /** Store the parent as a slider so that you don't have to keep casting it  */
  SuperSlider *parent;

  /** Store a bool to determine if the alternate handle has been activated  */
  bool handleActivated;

private:
  /** Store the filter for installation on the qguiapp */
  SliderEventFilter *filter;

  public slots:
    /** Sets the value of the handle with respect to the slider */
    void setValue(double value);
};
