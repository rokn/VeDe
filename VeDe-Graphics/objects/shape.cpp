#include "shape.h"

gx::Shape::Shape()
{
    addProperty("stroke-width", PROP_FLOAT);
    addProperty("stroke-color", PROP_COLOR);
    addProperty("back-color", PROP_COLOR);
}

void gx::Shape::paintSelf(gx::CustomPainter &painter) const
{
    painter.setStrokeWidth(getProp("stroke-width")->toFloat());
    painter.setStrokeColor(getProp("stroke-color")->toColor());
}
