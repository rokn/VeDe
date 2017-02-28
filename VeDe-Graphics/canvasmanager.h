#ifndef CANVASMANAGER_H
#define CANVASMANAGER_H

#include <QString>
#include "canvas.h"

namespace gx
{
class CanvasManager
{
public:
    virtual bool saveCanvas(std::string filename, const Canvas* canvas) = 0;
    virtual Canvas* loadCanvas(std::string filename) = 0;
};
}

#endif // CANVASMANAGER_H
