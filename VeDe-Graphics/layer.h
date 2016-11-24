#ifndef LAYER_H
#define LAYER_H

#include "objects/gobject.h"

namespace gx
{
class Layer : public GObject
{
public:
    Layer();

protected:
    void paintSelf(CustomPainter& painter) const;
};
}

#endif // LAYER_H
