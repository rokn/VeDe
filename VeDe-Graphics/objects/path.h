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

    QList<Vertex> vertices() const;

    QList<bool> controls() const;

    const QPainterPath& drawnPath() const;

    QRectF boundingBox() const;

private:
    QList<Vertex> m_vertices;
    QList<bool> m_controls;
    QPainterPath m_drawnPath;

    void constructPath();
};
}

#endif // PATH_H
