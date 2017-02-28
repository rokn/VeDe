#include "gobjectmapper.h"
#include "objects/ellipsegraphicsitem.h"
#include "objects/rectgraphicsitem.h"
#include "objects/linegraphicsitem.h"
#include "objects/pathgraphicsitem.h"
#include "objects/ellipse.h"
#include "objects/line.h"
#include "objects/rectangle.h"
#include "objects/path.h"
#include "layer.h"

GObjectMapper::GObjectType GObjectMapper::getObjectType(gx::SharedGObject object)
{
    if(std::dynamic_pointer_cast<gx::Ellipse>(object) != nullptr) {
        return GObjectType::Ellipse;
    }
    else if(std::dynamic_pointer_cast<gx::Rectangle>(object) != nullptr) {
        return GObjectType::Rectangle;
    }
    else if(std::dynamic_pointer_cast<gx::Line>(object) != nullptr) {
        return GObjectType::Line;
    }
    else if(std::dynamic_pointer_cast<gx::Path>(object) != nullptr) {
        return GObjectType::Path;
    }
    else if(std::dynamic_pointer_cast<gx::Layer>(object) != nullptr) {
        return GObjectType::Layer;
    }
}

QGraphicsItem *GObjectMapper::mapToGraphicsItem(gx::SharedGObject object)
{
    GObjectType type = getObjectType(object);
    QGraphicsItem* item = nullptr;

    switch(type)
    {
        case GObjectType::Ellipse:
            item = new EllipseGraphicsItem(std::dynamic_pointer_cast<gx::Ellipse>(object));
            break;
        case GObjectType::Rectangle:
            item = new RectGraphicsItem(std::dynamic_pointer_cast<gx::Rectangle>(object));
            break;
        case GObjectType::Line:
            item = new LineGraphicsItem(std::dynamic_pointer_cast<gx::Line>(object));
            break;
        case GObjectType::Path:
            item = new PathGraphicsItem(std::dynamic_pointer_cast<gx::Path>(object));
            break;
        default:break;
    }

    return item;
}
