#ifndef PATHTOOL_H
#define PATHTOOL_H

#include "shapetool.h"
#include <memory>
#include "objects/path.h"
#include "vertex.h"

namespace gx
{
class PathTool : public ShapeTool
{
public:
    PathTool(Canvas* canvas);

private:
    std::shared_ptr<Path> m_path;
    Vertex m_startPoint;

//    void restrictPos(const Vertex &p1, Vertex& p2);
//    void moveEndPoint();
};
}

#endif // PATHTOOL_H
