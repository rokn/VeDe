#ifndef TRANSLATECOMMAND_H
#define TRANSLATECOMMAND_H


#include "canvascommand.h"
#include <QList>

namespace gx
{
class TranslateCommand : public CanvasCommand
{
public:
    TranslateCommand(const QList<std::shared_ptr<GObject>>& objects, bool select = true);
    TranslateCommand(const QList<std::shared_ptr<GObject>>& objects, Canvas* canvas, bool select = true);
    TranslateCommand(const std::shared_ptr<GObject>& object, bool select = true);
    TranslateCommand(const std::shared_ptr<GObject>& object, Canvas* canvas, bool select = true);

    int execute();
    int undo();

private:
    QList<std::shared_ptr<GObject>> m_objects;
};
}

#endif // TRANSLATECOMMAND_H
