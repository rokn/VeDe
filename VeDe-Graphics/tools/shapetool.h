#ifndef SHAPETOOL_H
#define SHAPETOOL_H

#include "restrictabletool.h"
#include "objects/shape.h"

namespace gx
{
class ShapeTool : public RestrictableTool
{
public:
    ShapeTool(Canvas* canvas);



protected:
    void initStates(bool includeTransitions = true);
    void setShape(const std::shared_ptr<Shape> &shape);

    virtual bool startShape(Vertex mousePos);
    virtual void moveControl(Vertex mousePos);

    QString m_startState;
    QString m_placeFirstState;
    QString m_moveState;
    QString m_finishedState;

    std::shared_ptr<Shape> m_shape;
};
}

#endif // SHAPETOOL_H
