#include "shapetool.h"
#include "properties/propertynames.h"

gx::ShapeTool::ShapeTool(gx::Canvas *canvas)
    :RestrictableTool(canvas)
{
    addProperty(PROP::STROKE_WIDTH, PROP_FLOAT)->toFloat() = 1.0f;
}
