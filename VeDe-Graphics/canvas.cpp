#include "canvas.h"

gx::Canvas::Canvas()
    :m_root(new Layer)
{
}

gx::Canvas::Canvas(std::unique_ptr<GObject> &root)
{
    m_root = std::move(root);
    m_currCommand = 0;
}

gx::Canvas::~Canvas()
{
    foreach(auto command, m_commandHistory)
    {
        delete command;
    }
}

std::unique_ptr<gx::GObject> const& gx::Canvas::root() const
{
    return m_root;
}

int gx::Canvas::executeCommand(gx::Command* command)
{
    int result = command->execute();

    if(result == 0)
    {
        m_commandHistory.append(command);
        m_currCommand++;
    }

    return result;
}

int gx::Canvas::undoCommand()
{
    int result = -1;
    if(m_currCommand)
    {
        result = m_commandHistory.value(m_currCommand)->undo();

        if(result == 0)
        {
            m_currCommand--;
        }
    }

    return result;
}
