#ifndef TRANSLATECOMMAND_H
#define TRANSLATECOMMAND_H


#include "canvascommand.h"
#include <QList>

namespace gx
{
class TranslateCommand : public CanvasCommand
{
public:
    TranslateCommand(Vertex translation);

protected:
    int executeOnObject(SharedGObject obj, QRectF& redrawRect, bool reverse = false);

private:
    Vertex m_translation;
};
}

#endif // TRANSLATECOMMAND_H
