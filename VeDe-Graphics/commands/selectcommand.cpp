#include "selectcommand.h"

gx::SelectCommand::SelectCommand(bool select)
    :m_select(select)
{
}

int gx::SelectCommand::executeOnObject(gx::SharedGObject obj, QRectF &redrawRect, bool reverse)
{
    if(m_select != reverse)
        getCanvas()->selectObject(obj);
    else
        getCanvas()->deselectObject(obj);

    redrawRect = redrawRect.united(obj->boundingBox());
    return 0;
}
