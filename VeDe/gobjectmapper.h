#ifndef GOBJECTMAPPER_H
#define GOBJECTMAPPER_H

#include "objects/gobject.h"
#include <QGraphicsItem>

namespace GObjectMapper
{
    QGraphicsItem* mapToGraphicsItem(gx::SharedGObject object);
}

#endif // GOBJECTMAPPER_H
