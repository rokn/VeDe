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
    bool m_dragging;
    bool m_union;

    void selectObjects(QRectF rect);

    void updateSelection(Vertex cursor);
    void updateTranslation(Vertex cursor);
    void updateRotation(Vertex cursor);
    void updateScaling(Vertex cursor);
};
}

#endif // SELECTTOOL_H
