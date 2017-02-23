#ifndef IPAINTER_H
#define IPAINTER_H

#include "vertex.h"
#include "color.h"
#include <QList>
#include <QPainterPath>

namespace gx
{
class CustomPainter
{
public:
    virtual void drawLine(double x1, double y1, double x2, double y2) = 0;
    void drawLine(Vertex start, Vertex end);

    virtual void drawEllipse(double cX, double cY, double rX, double rY) = 0;
    void drawEllipse(Vertex center, Vertex radius);

    virtual void drawRectangle(double upLeftX, double upLeftY, double downRightX, double downRightY) = 0;
    void drawRectangle(Vertex upLeft, Vertex downRight);

    virtual void drawPath(QList<Vertex> vertices, QList<bool> moves) = 0;
    virtual void drawPath(QPainterPath& path) = 0;

    virtual void setStrokeWidth(double width) = 0;
    virtual void setStrokeColor(const Color& color) = 0;
    virtual void setBackColor(const Color& color) = 0;
    virtual void setZoomFactor(double zoomFactor) = 0;
    virtual void setTransform(QTransform transform) = 0;
};
}

#endif // IPAINTER_H
