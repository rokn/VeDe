#include "gobjecttypes.h"
#include "objects/ellipse.h"
#include "objects/line.h"
#include "objects/rectangle.h"
#include "objects/path.h"
#include "layer.h"

GObjectTypes::GObjectType GObjectTypes::getObjectType(gx::SharedGObject object)
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
