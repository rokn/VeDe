#ifndef QTCUSTOMPAINTER_H
#define QTCUSTOMPAINTER_H

#include "custompainter.h"
#include "vertex.h"
#include <QPaintDevice>
#include <QPainter>

class QtCustomPainter : public gx::CustomPainter
{
public:
    QtCustomPainter(QPainter* painter);
    void drawLine(double x1, double y1, double x2, double y2);
    void drawEllipse(double cX, double cY, double rX, double rY);
    void drawRectangle(double upLeftX, double upLeftY, double downRightX, double downRightY);
    void drawPath(QList<gx::Vertex> vertices, QList<bool> controls);
    void drawPath(QPainterPath& path);

    void setStrokeWidth(double width);
    void setStrokeColor(const gx::Color &color);
    void setBackColor(const gx::Color& color);
    void setZoomFactor(double zoomFactor);
    void setTransform(QTransform transform);
    void resetTransform();

    void setPainter(QPainter *painter);

private:
    void onChangePen();
    void onChangeBrush();

    QPainter* m_painter;
    QPen m_pen;
    QBrush m_brush;
    QTransform m_oldTransform;
};

#endif // QTCUSTOMPAINTER_H
