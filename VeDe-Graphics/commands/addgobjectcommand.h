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

protected:
    int executeOnObject(SharedGObject obj, QRectF& redrawRect, bool reverse = false);

private:
    bool m_add;
};
}

#endif // ADDLINECOMMAND_H
