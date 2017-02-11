#include "canvascommand.h"

gx::CanvasCommand::CanvasCommand(gx::Canvas *canvas)
    :m_canvas(canvas)
{
}

gx::Canvas* gx::CanvasCommand::getCanvas() const
{
    return m_canvas;
}

void gx::CanvasCommand::setCanvas(Canvas* canvas)
{
    m_canvas = canvas;
}

void gx::CanvasCommand::setObjects(const QList<gx::SharedGObject> &objects)
{
    m_objects = objects;
}

const QList<gx::SharedGObject > &gx::CanvasCommand::getObjects() const
{
    return m_objects;
}

void gx::CanvasCommand::setObject(const gx::SharedGObject &object)
{
    m_objects.clear();
    m_objects.append(object);
}
