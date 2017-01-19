#ifndef IPAINTER_H
#define IPAINTER_H

#include "vertex.h"
#include "color.h"
#include <QList>

namespace gx
{
class CustomPainter
{
public:
    virtual void drawLine(float x1, float y1, float x2, float y2) = 0;
    void drawLine(Vertex start, Vertex end);

    virtual void drawEllipse(float cX, float cY, float rX, float rY) = 0;
    void drawEllipse(Vertex center, Vertex radius);

    virtual void drawRectangle(float upLeftX, float upLeftY, float downRightX, float downRightY) = 0;
    void drawRectangle(Vertex upLeft, Vertex downRight);

    virtual void drawPath(QList<Vertex> vertices, QList<int> moves) = 0;

    virtual void setStrokeWidth(float width) = 0;
    virtual void setStrokeColor(const Color& color) = 0;
    virtual void setBackColor(const Color& color) = 0;
    virtual void setZoomFactor(float zoomFactor) = 0;
};
}

#endif // IPAINTER_H
