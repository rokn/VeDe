#ifndef SHAPE_H
#define SHAPE_H

#include "gobject.h"

namespace gx
{
class Shape : public GObject
{
public:
    Shape();

protected:
    void paintSelf(CustomPainter& painter) const;
};
}

#endif // SHAPE_H
