#ifndef CANVASCOMMAND_H
#define CANVASCOMMAND_H

#include "command.h"
#include "canvas.h"

namespace gx
{
class CanvasCommand : public Command
{
public:
    CanvasCommand(Canvas* canvas = nullptr);

    Canvas *getCanvas() const;
    void setCanvas(Canvas *canvas);

protected:
    Canvas* m_canvas;
};
}

#endif // CANVASCOMMAND_H
