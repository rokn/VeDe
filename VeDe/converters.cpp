#include "converters.h"

QColor Converters::toQColor(const gx::Color &c)
{
    return QColor(c.r(), c.g(), c.b(), c.a());
}

gx::Color Converters::toGxColor(const QColor &c)
{
    return gx::Color(c.red(), c.green(), c.blue(), c.alpha());
}

QPointF Converters::toPoint(const gx::Vertex &v)
{
    return QPointF(v.x(), v.y());
}

gx::Vertex Converters::toVertex(const QPointF &p)
{
    return gx::Vertex(p.x(),p.y());
}
