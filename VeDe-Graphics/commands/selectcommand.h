#ifndef SELECTCOMMAND_H
#define SELECTCOMMAND_H

#include "canvascommand.h"
#include <QList>

namespace gx
{
class SelectCommand : public CanvasCommand
{
public:
    SelectCommand(bool select = true);

protected:
    int executeOnObject(SharedGObject obj, QRectF& redrawRect, bool reverse = false);

private:
    bool m_select;
};
}

#endif // SELECTCOMMAND_H
