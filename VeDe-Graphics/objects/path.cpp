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

void gx::Path::paintSelf(gx::CustomPainter &painter) const
{
    Shape::paintSelf(painter);
    painter.drawPath(m_vertices, m_moves);
}
