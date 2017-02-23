#ifndef PATH_H
#define PATH_H

#include "custompainter.h"
#include "vertex.h"
#include "shape.h"
#include <QList>
#include <QPainterPath>


namespace gx
{
class Path : public Shape
{
public:
    Path();

    void addPoint(Vertex vertex);
    void changeLastPoint(Vertex vertex);
    void removeLastPoint();
    void addControlPoint(Vertex control);
    void changeLastControl(Vertex control);
    void removeLastControl();
    void closePath();

    QList<Vertex> vertices() const;

    QList<bool> controls() const;

    const QPainterPath& drawnPath() const;

protected:
    QRectF shapeBoundingBox() const;
    bool shapeContainsPoint(const gx::Vertex &point) const;

    void updateControlPoints();

private:
    QList<Vertex> m_vertices;
    QList<bool> m_controls;
    QPainterPath m_drawnPath;
    bool m_closed;

    void constructPath();
};
}

#endif // PATH_H
