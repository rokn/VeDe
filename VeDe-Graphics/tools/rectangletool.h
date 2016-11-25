#ifndef RECTANGLETOOL_H
#define RECTANGLETOOL_H

#include "tool.h"
#include "objects/rectangle.h"

namespace gx
{
class RectangleTool : public Tool
{
public:
    RectangleTool(Canvas* canvas);

private:
    std::shared_ptr<Rectangle> m_rect;
    Vertex anchorPoint;
};
}

#endif // RECTANGLETOOL_H
