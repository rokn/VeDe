#include "addgobjectcommand.h"

gx::AddGObjectCommand::AddGObjectCommand(std::shared_ptr<GObject> object)
    :m_object(object)
{
}

gx::AddGObjectCommand::AddGObjectCommand(std::shared_ptr<GObject> object, gx::Canvas *canvas)
    :CanvasCommand(canvas), m_object(object)
{
}

int gx::AddGObjectCommand::execute()
{
    m_canvas->addToCurrLayer(m_object);
    return 0;
}

int gx::AddGObjectCommand::undo()
{
    //TODO: Implement
    return -1;
}
