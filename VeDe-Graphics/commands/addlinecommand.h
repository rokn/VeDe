#ifndef ADDLINECOMMAND_H
#define ADDLINECOMMAND_H

#include "canvascommand.h"
#include "line.h"

namespace gx
{
class AddLineCommand : public CanvasCommand
{
public:
    AddLineCommand(std::shared_ptr<Line> line);
    AddLineCommand(std::shared_ptr<Line> line, Canvas* canvas);

    int execute();
    int undo();

private:
    std::shared_ptr<Line> m_line;
};
}

#endif // ADDLINECOMMAND_H
