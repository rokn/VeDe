#include "shape.h"
#include "properties/propertyfactory.h"
#include "properties/propertynames.h"
#include "canvas.h"

gx::Shape::Shape()
{
    PropertyFactory::addShapeProperties(this);
//    setSelected(true);
}

gx::Shape::~Shape()
{
    getCanvas()->onZoomChange() -= m_canvasZoomHandlerId;
}

bool gx::Shape::isGuiElement() const
{
    return m_guiElement;
}

void gx::Shape::setGuiElement(bool guiElement)
{
    if(guiElement == m_guiElement) return;

    m_guiElement = guiElement;

    if(guiElement == true)
    {
        if(getCanvas() != nullptr){
            getCanvas()->onZoomChange() += [=](float zoom){
                this->onCanvasZoomChange(zoom);
            };

            m_canvasZoomHandlerId = getCanvas()->onZoomChange().lastAdded();
        }

        onCanvasZoomChange(getCanvas()->getZoomFactor());
    }
}

void gx::Shape::fixBoxForStrokeWidth(QRectF &rect, float factor) const
{
    float strokeWidth = getProp(PROP::STROKE_WIDTH)->toFloat() * factor;
    rect.setBottom(rect.bottom() + strokeWidth);
    rect.setTop(rect.top() - strokeWidth);
    rect.setLeft(rect.left() - strokeWidth);
    rect.setRight(rect.right() + strokeWidth);
}

void gx::Shape::onCanvasZoomChange(float zoomFactor)
{
    if(this->isGuiElement()) {
        getProp(gx::PROP::STROKE_WIDTH)->toFloat() = 1.0f / zoomFactor;
    }
}
