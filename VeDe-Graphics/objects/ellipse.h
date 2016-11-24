#ifndef CIRCLE_H
#define CIRCLE_H

#include "gobject.h"
#include "vertex.h"

namespace gx
{
class Ellipse : public GObject
{
public:
    Ellipse();
    Ellipse(Vertex center, Vertex radius);

    Vertex center() const;
    void setCenter(const Vertex &center);

    Vertex radius() const;
    void setRadius(const Vertex &radius);

    void paintSelf(CustomPainter& painter) const;

private:
    Vertex m_center;
    Vertex m_radius;
};
}

#endif // CIRCLE_H
