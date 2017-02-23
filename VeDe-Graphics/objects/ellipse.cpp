#include "ellipse.h"
#include "converters.h"
#include "helpers.h"
#include <QPointF>
#include <QtMath>

gx::Ellipse::Ellipse()
    :Ellipse(Vertex(), Vertex())
{
}

gx::Ellipse::Ellipse(Vertex center, Vertex radius)
    :m_center(center), m_radius(radius)
{
    onChange() += [this](const GObject *o){
        updateControlPoints();
    };
    updateControlPoints();
}

gx::Ellipse::~Ellipse()
{
    foreach(auto point, m_controlPoints) {
        delete point;
    }
}

gx::Vertex gx::Ellipse::center() const
{
    return m_center;
}

void gx::Ellipse::setCenter(const Vertex &center)
{
    preChange();
    m_center = center;
    changed();
}

gx::Vertex gx::Ellipse::radius() const
{
    return m_radius;
}

void gx::Ellipse::setRadius(const Vertex &radius)
{
    preChange();
    m_radius = radius;
    changed();
}

void gx::Ellipse::shapeGetControlPoints(QList<ControlPoint*> &points)
{
    points.append(m_controlPoints);
}

void gx::Ellipse::updateControlPoints()
{
    foreach(auto point, m_controlPoints) {
        delete point;
    }

    m_controlPoints.clear();

    ControlPoint *forWidth = new ControlPoint(m_center - Vertex(m_radius.x(), 0));
    ControlPoint *forHeight = new ControlPoint(m_center - Vertex(0, m_radius.y()));

    forWidth->onMove() += [this](Vertex m) {
        m_radius.setX(m_radius.x() - m.x());
    };
    forWidth->setVertical(false);

    forHeight->onMove() += [this](Vertex m) {
        m_radius.setY(m_radius.y() - m.y());
    };
    forHeight->setHorizontal(false);

    m_controlPoints.append(forWidth);
    m_controlPoints.append(forHeight);

}

QRectF gx::Ellipse::shapeBoundingBox() const
{
    QPointF center = Converters::toPoint(this->center());
    QPointF radii = Converters::toPoint(this->radius());
    QRectF rect(center - radii, center + radii);
    fixBoxForStrokeWidth(rect);
    return getTransform().mapRect(rect); // TODO: Fix when rotating
}

bool gx::Ellipse::shapeContainsPoint(const gx::Vertex &point) const
{
//    gx::Vertex tc = center().transformed(getTransform());
//    gx::Vertex tp = point;
//    double xCoef = qPow(tp.x() - tc.x(), 2) / qPow(radius().x(), 2);
//    double yCoef = qPow(tp.y() - tc.y(), 2) / qPow(radius().y(), 2);
//    return (xCoef + yCoef) <= 1;
    return shapeBoundingBox().contains(Converters::toPoint(point));
}
