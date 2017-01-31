#include "ellipse.h"
#include "converters.h"
#include "helpers.h"
#include <QPointF>

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
    preChange();
    m_center = center;
    changed();
}

gx::Vertex gx::Ellipse::radius() const
{
    return m_radius;
}

void gx::Ellipse::setRadius(const Vertex &radius)
{
    preChange();
    m_radius = radius;
    changed();
}

QRectF gx::Ellipse::boundingBox() const
{
    QRectF baseBox = GObject::boundingBox();
    QPointF center = Converters::toPoint(this->center());
    QPointF radii = Converters::toPoint(this->radius());
    return baseBox.united(QRectF(center - radii, center + radii));
}
