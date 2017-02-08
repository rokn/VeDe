#include "line.h"
#include "helpers.h"
#include "converters.h"
#include "properties/propertynames.h"
#include <QtMath>

gx::Line::Line()
{
}

gx::Line::Line(Vertex start, Vertex end)
    :m_start(start), m_end(end)
{
}

gx::Vertex gx::Line::end() const
{
    return m_end;
}

void gx::Line::setEnd(const Vertex &end)
{
    preChange();
    m_end = end;
    changed();
}

gx::Vertex gx::Line::start() const
{
    return m_start;
}

void gx::Line::setStart(const Vertex &start)
{
    preChange();
    m_start = start;
    changed();
}

QRectF gx::Line::boundingBox() const
{
    QRectF baseBox = GObject::boundingBox();
    QPointF p1, p2;
    p1 = Converters::toPoint(start());
    p2 = Converters::toPoint(end());
    QPointF tl,dr;
    tl.setX(qMin(p1.x(), p2.x()));
    tl.setY(qMin(p1.y(), p2.y()));
    dr.setX(qMax(p1.x(), p2.x()));
    dr.setY(qMax(p1.y(), p2.y()));
    QRectF rect(tl,dr);
    fixBoxForStrokeWidth(rect, .7f);
    return baseBox.united(rect);
}

bool gx::Line::containsPoint(const gx::Vertex &point) const
{
    return distanceToPoint(point) <= getProp(PROP::STROKE_WIDTH)->toFloat();
}

float gx::Line::distanceToPoint(const gx::Vertex &point) const
{
    float lengthSquared = (m_end - m_start).lengthSquared();

    if(lengthSquared < 0.00001) return m_start.distance(point);

    float t = qMax(0.f, qMin(1.f, (point - m_start) * (m_end - m_start) / lengthSquared));
    Vertex projection = m_start + (m_end - m_start) * t;
    return point.distance(projection);
}
