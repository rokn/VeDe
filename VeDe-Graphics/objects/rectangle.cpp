#include "rectangle.h"

gx::Rectangle::Rectangle()
{

}

gx::Rectangle::Rectangle(gx::Vertex upLeft, gx::Vertex downRight)
    :m_upLeft(upLeft), m_downRight(downRight)
{
}

gx::Vertex gx::Rectangle::getUpLeft() const
{
    return m_upLeft;
}

void gx::Rectangle::setUpLeft(const Vertex &value)
{
    m_upLeft = value;
}

gx::Vertex gx::Rectangle::getDownRight() const
{
    return m_downRight;
}

void gx::Rectangle::setDownRight(const Vertex &value)
{
    m_downRight = value;
}

void gx::Rectangle::paintSelf(gx::CustomPainter &painter) const
{
    Shape::paintSelf(painter);
    painter.drawRectangle(m_upLeft, m_downRight);
}
