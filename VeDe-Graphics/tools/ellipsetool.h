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

protected:
    bool startShape(Vertex mousePos);
    void moveControl(Vertex mousePos);

private:
    Ellipse* m_ellipse;
};
}

#endif // ELLIPSETOOL_H
