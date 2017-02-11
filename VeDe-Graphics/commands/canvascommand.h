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

    void setObjects(const QList<SharedGObject>& objects);
    const QList<SharedGObject>& getObjects() const;

    void setObject(const SharedGObject& object);

protected:
    Canvas* m_canvas;
    QList<SharedGObject> m_objects;
};
}

#endif // CANVASCOMMAND_H
