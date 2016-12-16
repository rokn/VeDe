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
    void drawRectangle(float upLeftX, float upLeftY, float downRightX, float downRightY);

    void setStrokeWidth(float width);
    void setStrokeColor(const gx::Color &color);
    void setBackColor(const gx::Color& color);
    void setZoomFactor(float zoomFactor);

private:
    void onChangePen();
    void onChangeBrush();

    QPainter m_painter;
    QPen m_pen;
    QBrush m_brush;
};

#endif // QTCUSTOMPAINTER_H
