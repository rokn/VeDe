#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "shapetool.h"
#include "objects/rectangle.h"

namespace gx
{
class RectangleTool : public ShapeTool
{
public:
    RectangleTool(Canvas* canvas);

private:
    std::shared_ptr<Rectangle> m_rect;
    Vertex anchorPoint;

    void restrictPoints(Vertex& upLeft, Vertex& downRight);
};
}

#endif // RECTANGLETOOL_H
