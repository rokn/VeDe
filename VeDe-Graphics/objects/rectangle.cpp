#include "rectangle.h"

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

void gx::Rectangle::paintSelf(gx::CustomPainter &painter)
{
    Shape::paintSelf(painter);
    painter.drawRectangle(m_topLeft, m_bottomRight);
}
