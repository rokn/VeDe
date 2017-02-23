#ifndef CONTROLPOINT_H
#define CONTROLPOINT_H

#include "event.h"
#include "vertex.h"


namespace gx
{
class ControlPoint
{
public:
    ControlPoint(Vertex startPosition);
    Event<Vertex>& onMove();

    void move(Vertex distance);

    bool selected() const;
    void setSelected(bool selected);

    Vertex position() const;
    void setPosition(const Vertex &position);

    static double getDistanceThreshold();

    bool getHorizontal() const;
    void setHorizontal(bool horizontal);

    bool getVertical() const;
    void setVertical(bool vertical);

private:
    Event<Vertex> m_onMove;
    bool m_selected;
    bool m_horizontal;
    bool m_vertical;
    Vertex m_position;
};
}

#endif // CONTROLPOINT_H
