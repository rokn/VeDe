#ifndef LINE_H
#define LINE_H

#include "gobject.h"
#include "vertex.h"

namespace gx
{
class Line : public GObject
{
public:
    Line();
    Line(Vertex start, Vertex end);

    Vertex start() const;
    void setStart(const Vertex &start);

    Vertex end() const;
    void setEnd(const Vertex &end);

protected:
    void paintSelf(CustomPainter& painter) const;

private:
    Vertex m_start;
    Vertex m_end;
};
}

#endif // LINE_H
