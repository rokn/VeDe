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
    ~Ellipse();

    Vertex center() const;
    void setCenter(const Vertex &center);

    Vertex radius() const;
    void setRadius(const Vertex &radius);


protected:
    QRectF shapeBoundingBox() const;
    bool shapeContainsPoint(const gx::Vertex &point) const;
    void shapeGetControlPoints(QList<ControlPoint *> &points);

    void updateControlPoints();

private:
    Vertex m_center;
    Vertex m_radius;

    QList<ControlPoint*> m_controlPoints;
};
}

#endif // CIRCLE_H
