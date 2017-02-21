#include "rectangletool.h"
#include <QtMath>

gx::RectangleTool::RectangleTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Rectangle tool");
    m_startState = "Place first corner";
    m_moveState = "Place second corner";
    initStates();
}

bool gx::RectangleTool::startShape(gx::Vertex mousePos)
{
    m_anchorPoint = mousePos;
    auto rect = std::make_shared<Rectangle>();
    m_rect = rect.get();
    m_rect->setTopLeft(m_anchorPoint);
    m_rect->setBottomRight(m_anchorPoint);
    setShape(rect);
    return true;
}

void gx::RectangleTool::moveControl(gx::Vertex mousePos)
{
    Vertex upLeft(qMin(mousePos.x(), m_anchorPoint.x()), qMin(mousePos.y(), m_anchorPoint.y()));
    Vertex downRight(qMax(mousePos.x(), m_anchorPoint.x()), qMax(mousePos.y(), m_anchorPoint.y()));

    if(isRestricted()) {
        restrictPoints(mousePos, upLeft, downRight);
    }

    //Disable buggy division by zero
    if (qAbs(downRight.x() - upLeft.x()) < 0.0001) {
        downRight.setX(downRight.x() + 0.0001);
    }
    if (qAbs(downRight.y() - upLeft.y()) < 0.0001) {
        downRight.setY(downRight.y() + 0.0001);
    }

    m_rect->setTopLeft(upLeft);
    m_rect->setBottomRight(downRight);
}

void gx::RectangleTool::restrictPoints(const gx::Vertex& cursor, gx::Vertex &upLeft, gx::Vertex &downRight)
{
    double maxDist = qMax(qAbs(upLeft.x() - downRight.x()), qAbs(upLeft.y() - downRight.y()));

    if(cursor.x() < m_anchorPoint.x()) {
        upLeft.setX(m_anchorPoint.x() - maxDist);
    } else {
        downRight.setX(m_anchorPoint.x() + maxDist);
    }
    if(cursor.y() < m_anchorPoint.y()) {
        upLeft.setY(m_anchorPoint.y() - maxDist);
    } else {
        downRight.setY(m_anchorPoint.y() + maxDist);
    }
}
