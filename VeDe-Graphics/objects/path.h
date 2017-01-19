#ifndef PATH_H
#define PATH_H

#include "custompainter.h"
#include "vertex.h"
#include "shape.h"
#include <QList>

namespace gx
{
class Path : public Shape
{
public:
    Path();

    void addPoint(Vertex vertex);
    void addMove(int move);

    void paintSelf(CustomPainter& painter) const;

private:
    QList<Vertex> m_vertices;
    QList<int> m_moves;
};
}

#endif // PATH_H
