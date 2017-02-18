#include "addgobjectcommand.h"

gx::AddGObjectCommand::AddGObjectCommand(bool add)
    :m_add(add)
{
}

int gx::AddGObjectCommand::executeOnObject(gx::SharedGObject obj, QRectF &redrawRect, bool reverse)
{
    if(m_add != reverse)
        getCanvas()->addToCurrLayer(obj);
    else
        obj->remove();

    return 0;
}
