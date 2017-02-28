#include "canvas.h"
#include "properties/propertyfactory.h"
#include "tools/tool.h"
#include "commands/selectcommand.h"
#include <QtMath>
#include <memory>

gx::Canvas::Canvas(SharedGObject root, double width, double height)
    :m_root(root), m_width(width), m_height(height)
{
    if(m_root == nullptr) {
        m_root = SharedGObject(new Layer);
        m_currLayer = std::shared_ptr<Layer>(new Layer);
        m_root->addChild(m_currLayer, m_root);
        m_root->setId(m_idCount++);
        m_root->setCanvas(this);
        m_currLayer->setId(m_idCount++);
        m_currLayer->setCanvas(this);
    }

    m_currCommand = 0;
    m_currTool = nullptr;
    m_locked = false;
    m_idCount = 0;
    m_zoomFactor = 1.0;
    PropertyFactory::addCanvasProperties(this);
    getProp("Stroke Color")->toColor().setR(255);
}

double gx::Canvas::getZoomFactor() const
{
    return m_zoomFactor;
}

void gx::Canvas::setZoomFactor(double zoomFactor)
{
    m_zoomFactor = zoomFactor;
    m_zoomFactor = qMax(0.02, m_zoomFactor);
    m_onZoomChange(m_zoomFactor);
}

double gx::Canvas::mapValueToZoom(double value) const
{
    return value * (1 / getZoomFactor());
}

void gx::Canvas::onAddObject(gx::SharedGObject object){}

gx::Tool *gx::Canvas::getCurrTool() const
{
    return m_currTool;
}

double gx::Canvas::getHeight() const
{
    return m_height;
}

void gx::Canvas::setHeight(double height)
{
    m_height = height;
}

gx::Event<gx::Tool *>& gx::Canvas::onToolChanged()
{
    return m_onToolChanged;
}

gx::Event<double>& gx::Canvas::onZoomChange()
{
    return m_onZoomChange;
}

bool gx::Canvas::isLocked() const
{
    return m_locked;
}

void gx::Canvas::lock()
{
    m_locked = true;
}

void gx::Canvas::unlock()
{
    m_locked = false;
}

QList<gx::SharedGObject > gx::Canvas::getSelectedObjects()
{
    return m_selectedObjects;
}

QRectF gx::Canvas::getSelectedObjectsBox()
{
    QRectF box;
    foreach(auto& obj, m_selectedObjects)
    {
        box = box.united(obj->boundingBox());
    }
    return box;
}

void gx::Canvas::clearSelectedObjects(bool withCommand)
{
    if(m_selectedObjects.size() <= 0) return;

    if(withCommand)
    {
        CanvasCommand* deselectCommand = new SelectCommand(false);
        deselectCommand->setCanvas(this);
        deselectCommand->setObjects(m_selectedObjects);
        executeCommand(deselectCommand);
    }
    else
    {
        QRectF redrawRect;

        foreach(auto& obj, m_selectedObjects)
        {
            deselectObject(obj);
            redrawRect = redrawRect.united(obj->boundingBox());
        }

        redraw(redrawRect);
        m_selectedObjects.clear();
    }
}

void gx::Canvas::selectObject(gx::SharedGObject obj)
{
    obj->setSelected(true);
    m_selectedObjects.append(obj);
}

void gx::Canvas::deselectObject(gx::SharedGObject obj)
{
    obj->setSelected(false);
    m_selectedObjects.removeOne(obj);
}

QRectF gx::Canvas::getBoundaries() const
{
    return QRectF(0, 0, m_width, m_height);
}

void gx::Canvas::addNewCommand(gx::Command *command)
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

double gx::Canvas::getWidth() const
{
    return m_width;
}

void gx::Canvas::setWidth(double width)
{
    m_width = width;
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

gx::SharedGObject gx::Canvas::root()
{
    return m_root;
}

gx::SharedGObject gx::Canvas::root() const
{
    return m_root;
}

int gx::Canvas::executeCommand(gx::Command* command)
{
    if(isLocked()) return -1;
    int result = command->execute();

    if(result == 0)
    {
        addNewCommand(command);
    }

    redraw();
    return result;
}

void gx::Canvas::addSilentCommand(gx::Command *command)
{
    if(isLocked()) return;

    addNewCommand(command);
}

int gx::Canvas::undoCommand()
{
    int result = -1;
    if (isLocked()) return result;

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
    if (isLocked()) return result;

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

void gx::Canvas::handleTransition(const UserEvent &transition)
{
    if(m_currTool != nullptr)
    {
        m_currTool->handleEvent(transition);
    }
}

void gx::Canvas::addToCurrLayer(gx::SharedGObject object)
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
    m_currTool->setCanvas(this);
    m_onToolChanged(m_currTool);
    redraw();
}
