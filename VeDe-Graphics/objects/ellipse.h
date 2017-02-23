#ifndef CIRCLE_H
#define CIRCLE_H

#include "shape.h"
#include "vertex.h"

namespace gx
{
class Ellipse : public Shape
{
public:
    Ellipse();
    Ellipse(Vertex center, Vertex radius);

    Vertex center() const;
    void setCenter(const Vertex &center);

    Vertex radius() const;
    void setRadius(const Vertex &radius);

protected:
    QRectF shapeBoundingBox() const;
    bool shapeContainsPoint(const gx::Vertex &point) const;

    void updateControlPoints();

private:
    Vertex m_center;
    Vertex m_radius;

};
}

#endif // CIRCLE_H
