#include "addlinecommand.h"

gx::AddLineCommand::AddLineCommand(std::shared_ptr<gx::Line> line)
    :m_line(line)
{
}

gx::AddLineCommand::AddLineCommand(std::shared_ptr<gx::Line> line, gx::Canvas *canvas)
    :CanvasCommand(canvas), m_line(line)
{
}

int gx::AddLineCommand::execute()
{
    m_canvas->root()->addChildren(m_line);
}

int gx::AddLineCommand::undo()
{
    //TODO: Implement
}
