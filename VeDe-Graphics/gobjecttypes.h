#ifndef GOBJECTTYPES_H
#define GOBJECTTYPES_H

#include "objects/gobject.h"

namespace GObjectTypes
{
    enum GObjectType {
        Layer,
        Line,
        Ellipse,
        Rectangle,
        Path
    };

    GObjectType getObjectType(gx::SharedGObject object);
}

#endif // GOBJECTTYPES_H
