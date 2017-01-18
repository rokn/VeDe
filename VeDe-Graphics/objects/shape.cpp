#include "shape.h"
#include "properties/propertyfactory.h"
#include "properties/propertynames.h"
#include "canvas.h"

gx::Shape::Shape()
{
    PropertyFactory::addShapeProperties(this);
}

void gx::Shape::paintSelf(gx::CustomPainter &painter) const
{
    if(isGuiElement() && getCanvas() != nullptr)
    {
        getProp("Stroke Width")->toFloat() = 1.0f / getCanvas()->getZoomFactor(); // Get this to an event of changing zoom
    }

    painter.setStrokeWidth(getProp(PROP::STROKE_WIDTH)->toFloat());
    painter.setStrokeColor(getProp(PROP::STROKE_COLOR)->toColor());
    painter.setBackColor(getProp(PROP::BACK_COLOR)->toColor());
}

bool gx::Shape::isGuiElement() const
{
    return m_guiElement;
}

void gx::Shape::setGuiElement(bool guiElement)
{
    m_guiElement = guiElement;
}
