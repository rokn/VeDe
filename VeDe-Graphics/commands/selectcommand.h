#ifndef SELECTCOMMAND_H
#define SELECTCOMMAND_H

#include "canvascommand.h"
#include <QList>

namespace gx
{
class SelectCommand : public CanvasCommand
{
public:
    SelectCommand(const QList<std::shared_ptr<GObject>>& objects, bool select = true);
    SelectCommand(const QList<std::shared_ptr<GObject>>& objects, Canvas* canvas, bool select = true);
    SelectCommand(const std::shared_ptr<GObject>& object, bool select = true);
    SelectCommand(const std::shared_ptr<GObject>& object, Canvas* canvas, bool select = true);

    int execute();
    int undo();

private:
    QList<std::shared_ptr<GObject>> m_objects;
    bool m_select;
};
}

#endif // SELECTCOMMAND_H
