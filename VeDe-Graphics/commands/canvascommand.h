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

    void setObjects(const QList<std::shared_ptr<GObject>>& objects);
    const QList<std::shared_ptr<GObject>>& getObjects() const;

    void setObject(const std::shared_ptr<GObject>>& object)

protected:
    Canvas* m_canvas;
    QList<std::shared_ptr<GObject>> m_objects;
};
}

#endif // CANVASCOMMAND_H
