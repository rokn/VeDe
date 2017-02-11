#include "ellipsetool.h"
#include <QtMath>

gx::EllipseTool::EllipseTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Ellipse tool");
    m_startState = "Place the center";
    m_moveState = "Choose radii";
    initStates();
}

bool gx::EllipseTool::startShape(gx::Vertex mousePos)
{
    m_ellipse = std::make_shared<Ellipse>();
    m_ellipse->setCenter(getCanvas()->getCursor());
    m_ellipse->setRadius(Vertex(0,0));
    setShape(m_ellipse);
    return true;
}

void gx::EllipseTool::moveControl(gx::Vertex mousePos)
{
    double rx = qAbs(mousePos.x() - m_ellipse->center().x());
    double ry = qAbs(mousePos.y() - m_ellipse->center().y());

    if(isRestricted()) {
        rx = qMax(rx, ry);
        ry = rx;
    }

    //Disable buggy division by zero
    if(rx < 0.00001){
        rx+=0.00001;
    }
    if(ry < 0.00001) {
        ry += 0.00001;
    }

    m_ellipse->setRadius(Vertex(rx, ry));
}
