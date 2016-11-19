#ifndef LINE_H
#define LINE_H

#include "graphics/gobject.h"
#include "graphics/vertex.h"

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

private:
    Vertex m_start;
    Vertex m_end;
};
}

#endif // LINE_H
