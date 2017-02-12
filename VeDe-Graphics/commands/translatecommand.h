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

    int execute();
    int undo();

private:
    Vertex m_translation;

    void applyTranslation(Vertex translation);
};
}

#endif // TRANSLATECOMMAND_H
