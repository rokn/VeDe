#include "gobjectmapper.h"
#include "gobjecttypes.h"
#include "objects/ellipsegraphicsitem.h"
#include "objects/rectgraphicsitem.h"
#include "objects/linegraphicsitem.h"
#include "objects/pathgraphicsitem.h"
#include "objects/ellipse.h"
#include "objects/line.h"
#include "objects/rectangle.h"
#include "objects/path.h"

QGraphicsItem *GObjectMapper::mapToGraphicsItem(gx::SharedGObject object)
{
    GObjectTypes::GObjectType type = GObjectTypes::getObjectType(object);
    QGraphicsItem* item = nullptr;

    switch(type)
    {
        case GObjectTypes::GObjectType::Ellipse:
            item = new EllipseGraphicsItem(std::dynamic_pointer_cast<gx::Ellipse>(object));
            break;
        case GObjectTypes::GObjectType::Rectangle:
            item = new RectGraphicsItem(std::dynamic_pointer_cast<gx::Rectangle>(object));
            break;
        case GObjectTypes::GObjectType::Line:
            item = new LineGraphicsItem(std::dynamic_pointer_cast<gx::Line>(object));
            break;
        case GObjectTypes::GObjectType::Path:
            item = new PathGraphicsItem(std::dynamic_pointer_cast<gx::Path>(object));
            break;
        default:break;
    }

    return item;
}
