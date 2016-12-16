#include "shape.h"
#include "properties/propertyfactory.h"
#include "properties/propertynames.h"

gx::Shape::Shape()
{
    PropertyFactory::addShapeProperties(this);
}

void gx::Shape::paintSelf(gx::CustomPainter &painter) const
{
    painter.setStrokeWidth(getProp(PROP::STROKE_WIDTH)->toFloat());
    painter.setStrokeColor(getProp(PROP::STROKE_COLOR)->toColor());
    painter.setBackColor(getProp(PROP::BACK_COLOR)->toColor());
}
