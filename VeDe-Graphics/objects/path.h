#ifndef PATH_H
#define PATH_H

#include "custompainter.h"
#include "vertex.h"
#include "shape.h"
#include <QList>


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

    void paintSelf(CustomPainter& painter);

    QList<Vertex> vertices() const;

    QList<bool> controls() const;

private:
    QList<Vertex> m_vertices;
    QList<bool> m_controls;
};
}

#endif // PATH_H
