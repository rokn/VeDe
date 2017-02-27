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

    int execute();
    int undo();

protected:
    Canvas* m_canvas;
    QList<SharedGObject> m_objects;

    virtual int executeOnObject(SharedGObject obj, QRectF& redrawRect, bool reverse = false) = 0;

private:
    int applyCommand(bool reverse);

};
}

#endif // CANVASCOMMAND_H
