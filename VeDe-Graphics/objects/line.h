#ifndef LINE_H
#define LINE_H

#include "shape.h"
#include "vertex.h"

namespace gx
{
class Line : public Shape
{
public:
    Line();
    Line(Vertex start, Vertex end);

    Vertex start() const;
    void setStart(const Vertex &start);

    Vertex end() const;
    void setEnd(const Vertex &end);

    QRectF boundingBox() const;

private:
    Vertex m_start;
    Vertex m_end;
};
}

#endif // LINE_H
