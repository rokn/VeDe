#include "vertex.h"

Vertex::Vertex()
{
}

Vertex::Vertex(float x, float y)
    :_x(x), _y(y)
{
}

float Vertex::x() const
{
    return _x;
}

void Vertex::setX(float x)
{
    _x = x;
}

float Vertex::y() const
{
    return _y;
}

void Vertex::setY(float y)
{
    _y = y;
}

Vertex::operator QPoint() const
{
    return QPoint(_x, _y);
}
