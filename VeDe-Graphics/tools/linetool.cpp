#include "linetool.h"
#include <QtMath>

gx::LineTool::LineTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Line tool");
    m_startState = "Place a point";
    m_moveState = "Place end point";
    initStates();
}

bool gx::LineTool::startShape(gx::Vertex mousePos)
{
    m_line = std::make_shared<Line>();
    m_line->setStart(mousePos);
    mousePos.setX(mousePos.x()+0.0001f);//Disable buggy division by zero
    m_line->setEnd(mousePos);
    setShape(m_line);
    return true;
}

void gx::LineTool::moveControl(gx::Vertex mousePos)
{
    Vertex pos = getCanvas()->getCursor();

    if(isRestricted())
    {
        restrictPos(m_line->start(), pos);
    }

    m_line->setEnd(pos);
}

void gx::LineTool::restrictPos(const gx::Vertex& p1, gx::Vertex &p2)
{
    unsigned int x_diff = qAbs(p2.x() - p1.x());
    unsigned int y_diff = qAbs(p2.y() - p1.y());
    unsigned int max_diff = qMax(x_diff, y_diff);
    int diff = x_diff - y_diff;

    if(qAbs(diff) > max_diff / 2)
    {
        if(diff > 0)
        {
            p2.setY(p1.y());
        }
        else
        {
            p2.setX(p1.x());
        }
    }
    else
    {
        if(p2.x() < p1.x() && p2.y() < p1.y()) {
            p2.setX(p1.x() - max_diff);
            p2.setY(p1.y() - max_diff);
        }
        else if(p2.x() > p1.x() && p2.y() < p1.y()) {
            p2.setX(p1.x() + max_diff);
            p2.setY(p1.y() - max_diff);
        }
        else if(p2.x() < p1.x() && p2.y() > p1.y()) {
            p2.setX(p1.x() - max_diff);
            p2.setY(p1.y() + max_diff);
        }
        else if(p2.x() > p1.x() && p2.y() > p1.y()) {
            p2.setX(p1.x() + max_diff);
            p2.setY(p1.y() + max_diff);
        }
    }
}
