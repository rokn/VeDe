#include "rectangle.h"
#include "converters.h"
#include "helpers.h"

gx::Rectangle::Rectangle()
{

}

gx::Rectangle::Rectangle(gx::Vertex upLeft, gx::Vertex downRight)
    :m_topLeft(upLeft), m_bottomRight(downRight)
{
}

gx::Vertex gx::Rectangle::getTopLeft() const
{
    return m_topLeft;
}

void gx::Rectangle::setTopLeft(const Vertex &value)
{
    preChange();
    m_topLeft = value;
    changed();
}

gx::Vertex gx::Rectangle::getBottomRight() const
{
    return m_bottomRight;
}

void gx::Rectangle::setBottomRight(const Vertex &value)
{
    preChange();
    m_bottomRight = value;
    changed();
}

QRectF gx::Rectangle::boundingBox() const
{
    QRectF baseBox = GObject::boundingBox();
    QPointF p1, p2;
    p1 = Converters::toPoint(getTopLeft());
    p2 = Converters::toPoint(getBottomRight());
    QRectF rect(p1,p2);
    fixBoxForStrokeWidth(rect);
    return baseBox.united(rect);
}
