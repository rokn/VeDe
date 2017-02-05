#ifndef SELECTTOOL_H
#define SELECTTOOL_H

#include "tool.h"
#include <QRectF>

namespace gx
{
class SelectTool : public Tool
{
public:
    SelectTool(Canvas* canvas);

    void drawGui(CustomPainter& painter) const;

private:
    QRectF m_selection;
    Vertex m_anchorPoint;
    bool m_selecting;
};
}

#endif // SELECTTOOL_H
