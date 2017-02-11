#include "propertyfactory.h"
#include "propertynames.h"

void gx::PropertyFactory::addShapeProperties(gx::PropertyHolder *propHolder)
{
    propHolder->addProperty(PROP::STROKE_WIDTH, PROP_DOUBLE)->toDouble() = 1.0f;
    propHolder->addProperty(PROP::STROKE_COLOR, PROP_COLOR);
    propHolder->addProperty(PROP::BACK_COLOR, PROP_COLOR);
}


void gx::PropertyFactory::addCanvasProperties(gx::PropertyHolder *propHolder)
{
    propHolder->addProperty(PROP::STROKE_COLOR, PROP_COLOR);
    propHolder->addProperty(PROP::BACK_COLOR, PROP_COLOR);
}

void gx::PropertyFactory::setShapePreviewProperties(gx::PropertyHolder *propHolder)
{
    PropertyFactory::addShapeProperties(propHolder);
    propHolder->getProp(PROP::STROKE_COLOR)->toColor() = Color(0,255,0,255);
    propHolder->getProp(PROP::BACK_COLOR)->toColor() = Color(0,0,0,0);
}
