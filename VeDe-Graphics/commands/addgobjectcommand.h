#ifndef ADDLINECOMMAND_H
#define ADDLINECOMMAND_H

#include "canvascommand.h"
#include <QList>
#include "objects/gobject.h"

namespace gx
{
class AddGObjectCommand : public CanvasCommand
{
public:
    AddGObjectCommand(std::shared_ptr<GObject> object, bool add = true);
    AddGObjectCommand(std::shared_ptr<GObject> object, Canvas* canvas, bool add = true);
    AddGObjectCommand(const QList<std::shared_ptr<GObject>>& objects, bool add = true);
    AddGObjectCommand(const QList<std::shared_ptr<GObject>>& objects, Canvas* canvas, bool add = true);

    int execute();
    int undo();

private:
    QList<std::shared_ptr<GObject>> m_objects;
    bool m_add;
};
}

#endif // ADDLINECOMMAND_H
