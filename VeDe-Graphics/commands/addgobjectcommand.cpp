#include "addgobjectcommand.h"

gx::AddGObjectCommand::AddGObjectCommand(std::shared_ptr<gx::Line> line)
    :m_line(line)
{
}

gx::AddGObjectCommand::AddGObjectCommand(std::shared_ptr<gx::Line> line, gx::Canvas *canvas)
    :CanvasCommand(canvas), m_line(line)
{
}

int gx::AddGObjectCommand::execute()
{
    m_canvas->addToCurrLayer(m_line);
    return 0;
}

int gx::AddGObjectCommand::undo()
{
    //TODO: Implement
    return -1;
}
