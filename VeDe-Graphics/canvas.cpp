#include "canvas.h"
#include "properties/propertyfactory.h"
#include "tools/tool.h"
#include <QtMath>
#include <memory>

gx::Canvas::Canvas(std::shared_ptr<GObject> root, QObject *parent)
    :PropertyHolder(parent), m_root(root)
{
    if(m_root == nullptr) {
        m_root = std::shared_ptr<GObject>(new Layer);
        m_currLayer = std::shared_ptr<Layer>(new Layer);
        m_root->addChild(m_currLayer, m_root);
        m_root->setId(m_idCount++);
        m_currLayer->setId(m_idCount++);
    } else {
        //Find layer from root
    }

    m_currCommand = 0;
    m_currTool = nullptr;
    m_idCount = 0;
    m_zoomFactor = 1.0f;
    PropertyFactory::addCanvasProperties(this);
    getProp("Stroke Color")->toColor().setR(255);
}

float gx::Canvas::getZoomFactor() const
{
    return m_zoomFactor;
}

void gx::Canvas::setZoomFactor(float zoomFactor)
{
    m_zoomFactor = zoomFactor;
    m_zoomFactor = qMax(0.02f, m_zoomFactor);
}

void gx::Canvas::onAddObject(std::shared_ptr<gx::GObject> object){}

gx::Tool *gx::Canvas::getCurrTool() const
{
    return m_currTool;
}

std::shared_ptr<gx::Layer> gx::Canvas::getCurrLayer() const
{
    return m_currLayer;
}

gx::Canvas::~Canvas()
{
    foreach(auto command, m_commandHistory)
    {
        delete command;
    }

    m_root->removeAllChildren();
}

std::shared_ptr<gx::GObject> gx::Canvas::root()
{
    return m_root;
}

int gx::Canvas::executeCommand(gx::Command* command)
{
    int result = command->execute();

    if(result == 0)
    {
        if(m_currCommand != m_commandHistory.size())
        {
            for(auto it = m_commandHistory.begin() + m_currCommand; it != m_commandHistory.end(); ++it)
            {
                delete (*it);
            }

            m_commandHistory.erase(m_commandHistory.begin() + m_currCommand, m_commandHistory.end());
        }

        m_commandHistory.append(command);
        m_currCommand++;
    }

    redraw();
    return result;
}

int gx::Canvas::undoCommand()
{
    int result = -1;
    if(m_currCommand > 0)
    {
        result = m_commandHistory.at(m_currCommand - 1)->undo();

        if(result == 0)
        {
            m_currCommand--;
        }
    }

    redraw();
    return result;
}

int gx::Canvas::redoCommand()
{
    int result = -1;
    if(m_currCommand < m_commandHistory.size())
    {
        result = m_commandHistory.at(m_currCommand)->execute();

        if(result == 0)
        {
            m_currCommand++;
        }
    }

    redraw();
    return result;
}

void gx::Canvas::handleTransition(const Transition &transition)
{
    if(m_currTool != nullptr)
    {
        m_currTool->handleEvent(transition);
    }
}

void gx::Canvas::addToCurrLayer(std::shared_ptr<gx::GObject> object)
{
    object->setId(m_idCount++);
    object->setCanvas(this);
    m_currLayer->addChild(object, m_currLayer);
    onAddObject(object);
}

void gx::Canvas::changeCurrTool(gx::Tool *newTool)
{
    if(m_currTool != nullptr)
    {
        m_currTool->setActive(false);
    }

    m_currTool = newTool;
    m_currTool->setActive(true);
//    emit activeToolChanged(m_currTool);
}
