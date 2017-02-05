#include "selectcommand.h"

gx::SelectCommand::SelectCommand(const QList<std::shared_ptr<gx::GObject> > &objects, bool select)
    :SelectCommand(objects, nullptr, select)
{
}

gx::SelectCommand::SelectCommand(const QList<std::shared_ptr<gx::GObject> > &objects, gx::Canvas *canvas, bool select)
    :CanvasCommand(canvas), m_objects(objects), m_select(select)
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
