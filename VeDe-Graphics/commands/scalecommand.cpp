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
    Vertex scale = (reverse) ? Vertex(1/m_scale.x(), 1/m_scale.y()) : m_scale;

    if (m_useAxis) {
        obj->scale(scale, QTransform::fromTranslate(m_axis.x(), m_axis.y()));
    } else {
        obj->scale(scale);
    }

    redrawRect = redrawRect.united(obj->boundingBox());
    return 0;
}
