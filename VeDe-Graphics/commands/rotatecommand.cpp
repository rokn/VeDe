#include "rotatecommand.h"
#include <QTransform>

gx::RotateCommand::RotateCommand(double rotation)
    :m_rotation(rotation), m_useAxis(false)
{
}

gx::RotateCommand::RotateCommand(double rotation, gx::Vertex axis)
    :m_rotation(rotation), m_axis(axis), m_useAxis(true)
{
}

int gx::RotateCommand::executeOnObject(gx::SharedGObject obj, QRectF &redrawRect, bool reverse)
{
    redrawRect = redrawRect.united(obj->boundingBox());
    double rotation = (reverse) ? -m_rotation : m_rotation;

    if (m_useAxis) {
        obj->rotate(rotation, QTransform::fromTranslate(m_axis.x(), m_axis.y()));
    } else {
        obj->rotate(rotation);
    }

    redrawRect = redrawRect.united(obj->boundingBox());
    return 0;
}
