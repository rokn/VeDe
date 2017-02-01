#ifndef PROPERTYFACTORY_H
#define PROPERTYFACTORY_H

#include "propertyholder.h"

namespace gx
{
namespace PropertyFactory
{
    void addShapeProperties(PropertyHolder* propHolder);
    void addCanvasProperties(PropertyHolder* propHolder);
    void setShapePreviewProperties(gx::PropertyHolder *propHolder);
};
}

#endif // PROPERTYFACTORY_H
