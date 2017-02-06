#include "addgobjectcommand.h"

gx::AddGObjectCommand::AddGObjectCommand(std::shared_ptr<GObject> object, bool add)
    :AddGObjectCommand(object, nullptr, add)
{
}

gx::AddGObjectCommand::AddGObjectCommand(std::shared_ptr<GObject> object, gx::Canvas *canvas, bool add)
    :CanvasCommand(canvas), m_add(add)
{
    m_objects.append(object);
}

gx::AddGObjectCommand::AddGObjectCommand(const QList<std::shared_ptr<gx::GObject> > &objects, bool add)
    :AddGObjectCommand(objects, nullptr, add)
{
}

gx::AddGObjectCommand::AddGObjectCommand(const QList<std::shared_ptr<gx::GObject>> &objects, gx::Canvas *canvas, bool add)
    :CanvasCommand(canvas), m_objects(objects), m_add(add)
{
}

int gx::AddGObjectCommand::execute()
{
    foreach(auto& obj, m_objects)
    {
        if(m_add){
            getCanvas()->addToCurrLayer(obj);
        } else {
            obj->remove();
        }
    }

    return 0;
}

int gx::AddGObjectCommand::undo()
{
    foreach(auto& obj, m_objects)
    {
        if(m_add){
            obj->remove();
        } else {
            getCanvas()->addToCurrLayer(obj);
        }
    }
    return 0;
}
