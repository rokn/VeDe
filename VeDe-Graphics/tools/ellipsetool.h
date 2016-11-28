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
    void moveRadii();
private:


    std::shared_ptr<Ellipse> m_ellipse;
    bool m_restricted;
};
}

#endif // ELLIPSETOOL_H
