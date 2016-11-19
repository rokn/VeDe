#include "vertex.h"

gx::Vertex::Vertex()
    :m_x(0.0f), m_y(0.0f)
{
}

gx::Vertex::Vertex(const Vertex &other)
    :m_x(other.x()), m_y(other.y())
{
}

gx::Vertex::Vertex(float x, float y)
    :m_x(x), m_y(y)
{
}

float gx::Vertex::x() const
{
    return m_x;
}

void gx::Vertex::setX(float x)
{
    m_x = x;
}

float gx::Vertex::y() const
{
    return m_y;
}

void gx::Vertex::setY(float y)
{
    m_y = y;
}
