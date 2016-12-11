#include "canvas.h"
#include "tools/tool.h"

gx::Canvas::Canvas()
    :m_root(new Layer)
{
    m_currLayer = new Layer();
    m_root->addChild(m_currLayer);
    initCommon();
}

gx::Canvas::Canvas(std::unique_ptr<GObject> *root)
{
    m_root = std::move(*root);
    initCommon();
}

void gx::Canvas::initCommon()
{
    m_currCommand = 0;
    m_currTool = nullptr;
}

gx::Canvas::~Canvas()
{
    foreach(auto command, m_commandHistory)
    {
        delete command;
    }
}

std::unique_ptr<gx::GObject> const& gx::Canvas::root()
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

    redraw();
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

    redraw();
    return result;
}

void gx::Canvas::handleEvent(const Transition &transition)
{
    if(m_currTool != nullptr)
    {
        m_currTool->handleEvent(transition);
    }
}

void gx::Canvas::addToCurrLayer(std::shared_ptr<gx::GObject> object)
{
    m_currLayer->addChild(object);
}

void gx::Canvas::changeCurrTool(gx::Tool *newTool)
{
    if(m_currTool != nullptr)
    {
        m_currTool->setActive(false);
    }

    m_currTool = newTool;
    m_currTool->setActive(true);
}
