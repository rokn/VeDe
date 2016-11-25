#ifndef RECTANGLE_H
#define RECTANGLE_H

#include "gobject.h"

namespace gx
{
class Rectangle : public GObject
{
public:
    Rectangle();
    Rectangle(Vertex upLeft, Vertex downRight);

    Vertex getUpLeft() const;
    void setUpLeft(const Vertex &value);

    Vertex getDownRight() const;
    void setDownRight(const Vertex &value);

    void paintSelf(CustomPainter &painter) const;

private:
    Vertex m_upLeft;
    Vertex m_downRight;
};
}

#endif // RECTANGLE_H
