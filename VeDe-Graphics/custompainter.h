#ifndef IPAINTER_H
#define IPAINTER_H

#include "vertex.h"

namespace gx
{
class CustomPainter
{
public:
    virtual void drawLine(int x1, int y1, int x2, int y2) = 0;
    void drawLine(Vertex start, Vertex end);
};
}

#endif // IPAINTER_H
