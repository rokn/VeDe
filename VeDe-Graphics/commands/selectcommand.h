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

    int execute();
    int undo();

private:
    bool m_select;
};
}

#endif // SELECTCOMMAND_H
