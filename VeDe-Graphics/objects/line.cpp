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

QRectF gx::Line::shapeBoundingBox() const
{
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
    return getTransform().mapRect(rect);
}

bool gx::Line::shapeContainsPoint(const gx::Vertex &point) const
{
    return distanceToPoint(point) <= getProp(PROP::STROKE_WIDTH)->toDouble();
}

double gx::Line::distanceToPoint(const gx::Vertex &point) const
{
    Vertex tStart = start().transformed(getTransform());
    Vertex tEnd = end().transformed(getTransform());
    double lengthSquared = (tEnd - tStart).lengthSquared();

    if(lengthSquared < 0.00001) return m_start.distance(point);

    double t = qMax(0., qMin(1., (point - tStart) * (tEnd - tStart) / lengthSquared));
    Vertex projection = tStart + (tEnd - tStart) * t;
    return point.distance(projection);
}
