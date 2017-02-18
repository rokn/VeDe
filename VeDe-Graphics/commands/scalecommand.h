#ifndef SCALECOMMAND_H
#define SCALECOMMAND_H


#include "canvascommand.h"
#include <QList>

namespace gx
{
class ScaleCommand : public CanvasCommand
{
public:
    ScaleCommand(Vertex scale);
    ScaleCommand(Vertex scale, Vertex axis);

protected:
    int executeOnObject(SharedGObject obj, QRectF& redrawRect, bool reverse = false);

private:
    Vertex m_scale;
    Vertex m_axis;
    bool m_useAxis;
};
}

#endif // SCALECOMMAND_H
