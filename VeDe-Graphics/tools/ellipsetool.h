#ifndef ELLIPSETOOL_H
#define ELLIPSETOOL_H

#include "shapetool.h"
#include "objects/ellipse.h"
#include <memory>

namespace gx
{
class EllipseTool : public ShapeTool
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
