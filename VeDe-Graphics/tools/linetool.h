#ifndef LINETOOL_H
#define LINETOOL_H

#include "shapetool.h"
#include <memory>
#include "objects/line.h"
#include "vertex.h"

namespace gx {
class LineTool : public ShapeTool
{
public:
    LineTool(Canvas* canvas);

protected:
    bool startShape(Vertex mousePos);
    void moveControl(Vertex mousePos);

private:
    std::shared_ptr<Line> m_line;

    void restrictPos(const Vertex &p1, Vertex& p2);
};
}

#endif // LINETOOL_H
