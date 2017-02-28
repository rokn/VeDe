#ifndef GOBJECTMAPPER_H
#define GOBJECTMAPPER_H

#include "objects/gobject.h"
#include <QGraphicsItem>

namespace GObjectMapper
{
    enum GObjectType {
        Layer,
        Line,
        Ellipse,
        Rectangle,
        Path
    };

    GObjectType getObjectType(gx::SharedGObject object);
    QGraphicsItem* mapToGraphicsItem(gx::SharedGObject object);
}

#endif // GOBJECTMAPPER_H
