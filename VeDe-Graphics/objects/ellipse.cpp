#include "ellipse.h"

gx::Ellipse::Ellipse()
{
}

gx::Ellipse::Ellipse(Vertex center, Vertex radius)
    :m_center(center), m_radius(radius)
{
}

gx::Vertex gx::Ellipse::center() const
{
    return m_center;
}

void gx::Ellipse::setCenter(const Vertex &center)
{
    m_center = center;
}

gx::Vertex gx::Ellipse::radius() const
{
    return m_radius;
}

void gx::Ellipse::setRadius(const Vertex &radius)
{
    m_radius = radius;
}

void gx::Ellipse::paintSelf(gx::CustomPainter &painter)
{
    Shape::paintSelf(painter);
    painter.drawEllipse(m_center, m_radius);
}
