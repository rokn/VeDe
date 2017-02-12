#ifndef VERTEX_H
#define VERTEX_H

#include <QTransform>

namespace gx
{
class Vertex
{
public:
    Vertex();
    Vertex(const Vertex& other);
    Vertex(double x, double y);

    double x() const;
    void setX(double x);

    double y() const;
    void setY(double y);

    Vertex& operator +=(const Vertex& other);
    Vertex& operator -=(const Vertex& other);

    Vertex operator +(const Vertex& other) const;
    Vertex operator -(const Vertex& other) const;
    double operator *(const Vertex& other) const;

    Vertex& operator +=(double& scalar);
    Vertex& operator -=(double& scalar);
    Vertex& operator *=(double& scalar);
    Vertex& operator /=(double& scalar);

    Vertex operator +(double& scalar) const;
    Vertex operator -(double& scalar) const;
    Vertex operator *(double& scalar) const;
    Vertex operator /(double& scalar) const;

    Vertex operator -() const;

    double distance(const Vertex& other) const;
    double length() const;
    double lengthSquared() const;

    Vertex transformed(const QTransform &transform) const;

private:
    double m_x;
    double m_y;
};
}

#endif // VERTEX_H
