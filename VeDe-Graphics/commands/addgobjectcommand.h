#ifndef ADDLINECOMMAND_H
#define ADDLINECOMMAND_H

#include "canvascommand.h"
#include "objects/gobject.h"

namespace gx
{
class AddGObjectCommand : public CanvasCommand
{
public:
    AddGObjectCommand(std::shared_ptr<GObject> object);
    AddGObjectCommand(std::shared_ptr<GObject> object, Canvas* canvas);

    int execute();
    int undo();

private:
    std::shared_ptr<GObject> m_object;
};
}

#endif // ADDLINECOMMAND_H
