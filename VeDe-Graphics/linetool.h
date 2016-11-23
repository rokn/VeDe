#ifndef LINETOOL_H
#define LINETOOL_H

#include "tool.h"
#include <memory>
#include "line.h"

namespace gx {
class LineTool : public Tool
{
public:
    LineTool(Canvas* canvas);

private:
    std::shared_ptr<Line> m_line;
};
}

#endif // LINETOOL_H
