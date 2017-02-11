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
    AddGObjectCommand(bool add = true);

    int execute();
    int undo();

private:
    bool m_add;
};
}

#endif // ADDLINECOMMAND_H
