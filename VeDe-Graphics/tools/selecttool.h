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
    Vertex m_startTranslation;
    Vertex m_rotationAxis;
    Vertex m_oldPosition;
    double m_oldAngle;
    bool m_oldAngleSet;
    bool m_useRotAxis;
    bool m_selecting;
    bool m_translating;
    bool m_rotating;
    bool m_scaling;
    bool m_union;

    void selectObjects(QRectF rect);

    void updateSelection(Vertex cursor);
    void updateTranslation(Vertex cursor);
    void updateRotation(Vertex cursor);
    void updateScaling(Vertex cursor);

    void endSelection();
    void endTranslation();
    void endRotation();
};
}

#endif // SELECTTOOL_H
