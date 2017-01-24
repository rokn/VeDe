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

    Vertex getUpLeft() const;
    void setUpLeft(const Vertex &value);

    Vertex getDownRight() const;
    void setDownRight(const Vertex &value);

    void paintSelf(CustomPainter &painter);

private:
    Vertex m_upLeft;
    Vertex m_downRight;
};
}

#endif // RECTANGLE_H
