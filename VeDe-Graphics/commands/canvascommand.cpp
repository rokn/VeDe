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
