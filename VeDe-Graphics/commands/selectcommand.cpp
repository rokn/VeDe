#include "selectcommand.h"

gx::SelectCommand::SelectCommand(bool select)
    :m_select(select)
{
}

int gx::SelectCommand::execute()
{
    QRectF redrawRect;
    foreach(auto& obj, m_objects)
    {
        if(m_select)
            getCanvas()->selectObject(obj);
        else
            getCanvas()->deselectObject(obj);

        redrawRect.united(obj->boundingBox());
    }

    getCanvas()->redraw(redrawRect);
    return 0;
}

int gx::SelectCommand::undo()
{
    QRectF redrawRect;
    foreach(auto& obj, m_objects)
    {
        if(m_select)
            getCanvas()->deselectObject(obj);
        else
            getCanvas()->selectObject(obj);

        redrawRect.united(obj->boundingBox());
    }

    getCanvas()->redraw(redrawRect);
    return 0;
}
