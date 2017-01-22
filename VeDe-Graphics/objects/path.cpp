#include "path.h"

gx::Path::Path()
{

}

void gx::Path::addPoint(gx::Vertex vertex)
{
    m_vertices.append(vertex);
}

void gx::Path::addMove(int move)
{
    m_moves.append(move);
}

void gx::Path::changeLastMove(int move)
{
    m_moves.last() = move;
}

void gx::Path::removeLastMove()
{
    m_moves.removeLast();
}

void gx::Path::changeLastPoint(gx::Vertex vertex)
{
    m_vertices.last().setX(vertex.x());
    m_vertices.last().setY(vertex.y());
}

void gx::Path::removeLastPoint()
{
    m_vertices.removeLast();
}

void gx::Path::paintSelf(gx::CustomPainter &painter) const
{
    Shape::paintSelf(painter);
    painter.drawPath(m_vertices, m_moves);
}
