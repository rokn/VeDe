#ifndef ROTATECOMMAND_H
#define ROTATECOMMAND_H


#include "canvascommand.h"
#include <QList>

namespace gx
{
class RotateCommand : public CanvasCommand
{
public:
    RotateCommand(double rotation);
    RotateCommand(double rotation, Vertex axis);

protected:
    int executeOnObject(SharedGObject obj, QRectF& redrawRect, bool reverse = false);

private:
    double m_rotation;
    Vertex m_axis;
    bool m_useAxis;
};
}

#endif // ROTATECOMMAND_H
