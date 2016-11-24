#ifndef QTCUSTOMPAINTER_H
#define QTCUSTOMPAINTER_H

#include "custompainter.h"
#include <QPaintDevice>
#include <QPainter>

class QtCustomPainter : public gx::CustomPainter
{
public:
    QtCustomPainter(QPaintDevice* canvas);
    void drawLine(float x1, float y1, float x2, float y2);
    void drawEllipse(float cX, float cY, float rX, float rY);
private:
    QPainter m_painter;
};

#endif // QTCUSTOMPAINTER_H
