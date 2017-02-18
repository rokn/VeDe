#include "scalecommand.h"
#include <QTransform>

gx::ScaleCommand::ScaleCommand(Vertex scale)
    :m_scale(scale), m_useAxis(false)
{
}

gx::ScaleCommand::ScaleCommand(gx::Vertex scale, gx::Vertex axis)
    :m_scale(scale), m_axis(axis), m_useAxis(true)
{
}

int gx::ScaleCommand::executeOnObject(gx::SharedGObject obj, QRectF &redrawRect, bool reverse)
{
    redrawRect = redrawRect.united(obj->boundingBox());
    Vertex scale = (reverse) ? (1.0/m_scale) : m_scale;

    if (m_useAxis) {
        obj->scale(scale, QTransform::fromTranslate(m_axis.x(), m_axis.y()));
    } else {
        obj->scale(scale);
    }

    redrawRect = redrawRect.united(obj->boundingBox());
    return 0;
}
