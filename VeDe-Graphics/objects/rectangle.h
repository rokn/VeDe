#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "shape.h"

namespace gx
{
class Rectangle : public Shape
{
public:
    Rectangle();
    Rectangle(Vertex upLeft, Vertex downRight);

    Vertex getTopLeft() const;
    void setTopLeft(const Vertex &value);

    Vertex getBottomRight() const;
    void setBottomRight(const Vertex &value);

    void paintSelf(CustomPainter &painter);

protected:
    QRectF shapeBoundingBox() const;
    bool shapeContainsPoint(const gx::Vertex &point) const;

private:
    Vertex m_topLeft;
    Vertex m_bottomRight;
};
}

#endif // RECTANGLE_H
