#ifndef LINE_H
#define LINE_H

#include "graphics/gobject.h"
#include "graphics/vertex.h"

class Line : public GObject
{
public:
    Line();
    Line(Vertex start, Vertex end);

private:
    Vertex _start;
    Vertex _end;
};

#endif // LINE_H
