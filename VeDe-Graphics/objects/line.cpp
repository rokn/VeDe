#include "line.h"
#include "helpers.h"
#include "converters.h"

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
    return baseBox.united(QRectF(tl,dr));
}
