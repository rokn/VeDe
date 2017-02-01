#include "shape.h"
#include "properties/propertyfactory.h"
#include "properties/propertynames.h"
#include "canvas.h"

gx::Shape::Shape()
{
    PropertyFactory::addShapeProperties(this);
}

bool gx::Shape::isGuiElement() const
{
    return m_guiElement;
}

void gx::Shape::setGuiElement(bool guiElement)
{
    m_guiElement = guiElement;
}

void gx::Shape::fixBoxForStrokeWidth(QRectF &rect, float factor) const
{
    float strokeWidth = getProp(PROP::STROKE_WIDTH)->toFloat() * factor;
    rect.setBottom(rect.bottom() + strokeWidth);
    rect.setTop(rect.top() - strokeWidth);
    rect.setLeft(rect.left() - strokeWidth);
    rect.setRight(rect.right() + strokeWidth);
}
