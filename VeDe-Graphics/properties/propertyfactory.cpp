#include "propertyfactory.h"
#include "propertynames.h"

void gx::PropertyFactory::addShapeProperties(gx::PropertyHolder *propHolder)
{
    propHolder->addProperty(PROP::STROKE_WIDTH, PROP_FLOAT)->toFloat() = 1.0f;
    propHolder->addProperty(PROP::STROKE_COLOR, PROP_COLOR);
    propHolder->addProperty(PROP::BACK_COLOR, PROP_COLOR);
}


void gx::PropertyFactory::addCanvasProperties(gx::PropertyHolder *propHolder)
{
    propHolder->addProperty(PROP::STROKE_COLOR, PROP_COLOR);
    propHolder->addProperty(PROP::BACK_COLOR, PROP_COLOR);
}
