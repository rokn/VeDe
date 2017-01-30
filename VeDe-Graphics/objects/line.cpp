#include "line.h"

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

void gx::Line::paintSelf(gx::CustomPainter &painter)
{
    Shape::paintSelf(painter);
    painter.drawLine(m_start, m_end);
}
