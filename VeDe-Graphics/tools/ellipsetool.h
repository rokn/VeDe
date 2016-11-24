#ifndef ELLIPSETOOL_H
#define ELLIPSETOOL_H

#include "tool.h"
#include "objects/ellipse.h"
#include <memory>

namespace gx
{
class EllipseTool : public Tool
{
public:
    EllipseTool(Canvas* canvas);

private:
    std::shared_ptr<Ellipse> m_ellipse;
};
}

#endif // ELLIPSETOOL_H
