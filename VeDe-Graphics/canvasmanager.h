#ifndef CANVASMANAGER_H
#define CANVASMANAGER_H

#include <QString>
#include "canvas.h"

namespace gx
{
class CanvasManager
{
public:
    virtual bool saveCanvas(QString filename, const Canvas* canvas) = 0;
    virtual Canvas* loadCanvas(QString filename) = 0;
};
}

#endif // CANVASMANAGER_H
