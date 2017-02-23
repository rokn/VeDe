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

QRectF gx::Rectangle::shapeBoundingBox() const
{
    QPointF p1, p2;
    p1 = Converters::toPoint(getTopLeft());
    p2 = Converters::toPoint(getBottomRight());
    QRectF rect(p1,p2);
    fixBoxForStrokeWidth(rect);
    return getTransform().mapRect(rect);
}

bool gx::Rectangle::shapeContainsPoint(const gx::Vertex &point) const
{
//    Vertex p1 = point - m_topLeft;
//    Vertex p2 = point - m_bottomRight;

//    return p1.x() > 0 && p1.y() > 0 && p2.x() < 0 && p2.y() < 0;
    return shapeBoundingBox().contains(Converters::toPoint(point));
}

void gx::Rectangle::updateControlPoints()
{
    ControlPoint *forTopLeft = new ControlPoint(m_topLeft);
    ControlPoint *forBottomRight = new ControlPoint(m_bottomRight);

    forTopLeft->onMove() += [this](Vertex m) {
        m_topLeft += m;
    };

    forBottomRight->onMove() += [this](Vertex m) {
        m_bottomRight += m;
    };

    addControlPoint(forTopLeft);
    addControlPoint(forBottomRight);
}
