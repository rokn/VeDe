#include "controlpoint.h"

gx::ControlPoint::ControlPoint(Vertex startPosition)
    :m_position(startPosition), m_horizontal(true), m_vertical(true), m_selected(false)
{
}

gx::Event<gx::Vertex>& gx::ControlPoint::onMove()
{
    return m_onMove;
}

void gx::ControlPoint::move(gx::Vertex distance)
{
    if(!m_horizontal) {
        distance.setX(0);
    }

    if(!m_vertical) {
        distance.setY(0);
    }

    m_position += distance;
    m_onMove(distance);
}

bool gx::ControlPoint::selected() const
{
    return m_selected;
}

void gx::ControlPoint::setSelected(bool selected)
{
    m_selected = selected;
}

gx::Vertex gx::ControlPoint::position() const
{
    return m_position;
}

void gx::ControlPoint::setPosition(const Vertex &position)
{
    move(position - m_position);
}

double gx::ControlPoint::getDistanceThreshold()
{
    return 5.5;
}

bool gx::ControlPoint::getVertical() const
{
    return m_vertical;
}

void gx::ControlPoint::setVertical(bool vertical)
{
    m_vertical = vertical;
}

bool gx::ControlPoint::getHorizontal() const
{
    return m_horizontal;
}

void gx::ControlPoint::setHorizontal(bool horizontal)
{
    m_horizontal = horizontal;
}
