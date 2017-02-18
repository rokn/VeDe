#include "translatecommand.h"

gx::TranslateCommand::TranslateCommand(gx::Vertex translation)
    :m_translation(translation)
{
}

int gx::TranslateCommand::executeOnObject(gx::SharedGObject obj, QRectF &redrawRect, bool reverse)
{
    auto translation = (reverse) ? -m_translation : m_translation;

    redrawRect = redrawRect.united(obj->boundingBox());
    obj->translate(translation);
    redrawRect = redrawRect.united(obj->boundingBox());

    return 0;
}
