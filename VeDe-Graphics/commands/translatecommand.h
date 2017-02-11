#ifndef TRANSLATECOMMAND_H
#define TRANSLATECOMMAND_H


#include "canvascommand.h"
#include <QList>

namespace gx
{
class TranslateCommand : public CanvasCommand
{
public:
    int execute();
    int undo();

private:
};
}

#endif // TRANSLATECOMMAND_H
