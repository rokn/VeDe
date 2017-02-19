#include "vertex.h"
#include "converters.h"
#include <QtMath>

gx::Vertex::Vertex()
    :m_x(0.0f), m_y(0.0f)
{
}

gx::Vertex::Vertex(const Vertex &other)
    :m_x(other.x()), m_y(other.y())
{
}

gx::Vertex::Vertex(double x, double y)
    :m_x(x), m_y(y)
{
}

double gx::Vertex::x() const
{
    return m_x;
}

void gx::Vertex::setX(double x)
{
    m_x = x;
}

double gx::Vertex::y() const
{
    return m_y;
}

void gx::Vertex::setY(double y)
{
    m_y = y;
}

gx::Vertex &gx::Vertex::operator +=(const gx::Vertex &other)
{
    this->m_x += other.x();
    this->m_y += other.y();
    return *this;
}

gx::Vertex &gx::Vertex::operator -=(const gx::Vertex &other)
{
    this->m_x -= other.x();
    this->m_y -= other.y();
    return *this;
}

gx::Vertex gx::Vertex::operator +(const gx::Vertex &other) const
{
    return Vertex(m_x + other.x(), m_y + other.y());
}

gx::Vertex gx::Vertex::operator -(const gx::Vertex &other) const
{
    return Vertex(m_x - other.x(), m_y - other.y());
}

double gx::Vertex::operator *(const gx::Vertex &other) const
{
    return m_x * other.x() + m_y * other.y();
}

gx::Vertex &gx::Vertex::operator +=(double scalar)
{
    this->m_x += scalar;
    this->m_y += scalar;
    return *this;
}

gx::Vertex &gx::Vertex::operator -=(double scalar)
{
    this->m_x -= scalar;
    this->m_y -= scalar;
    return *this;
}

gx::Vertex &gx::Vertex::operator *=(double scalar)
{
    this->m_x *= scalar;
    this->m_y *= scalar;
    return *this;
}

gx::Vertex &gx::Vertex::operator /=(double scalar)
{
    this->m_x /= scalar;
    this->m_y /= scalar;
    return *this;
}

gx::Vertex gx::Vertex::operator +(double scalar) const
{
    return Vertex(m_x + scalar, m_y + scalar);
}

gx::Vertex gx::Vertex::operator -(double scalar) const
{
    return Vertex(m_x - scalar, m_y - scalar);
}

gx::Vertex gx::Vertex::operator *(double scalar) const
{
    return Vertex(m_x * scalar, m_y * scalar);
}

gx::Vertex gx::Vertex::operator /(double scalar) const
{
    return Vertex(m_x / scalar, m_y / scalar);
}

gx::Vertex gx::Vertex::operator -() const
{
    return Vertex(-m_x, -m_y);
}

double gx::Vertex::distance(const gx::Vertex &other) const
{
    return qSqrt(qPow(other.x() - m_x, 2) + qPow(other.y() - m_y, 2));
}

double gx::Vertex::length() const
{
    return qSqrt(qPow(m_x, 2) + qPow(m_y, 2));
}

double gx::Vertex::lengthSquared() const
{
    return qPow(m_x, 2) + qPow(m_y, 2);
}

gx::Vertex gx::Vertex::transformed(const QTransform& transform) const
{
    QPointF transfPoint = transform.map(Converters::toPoint(*this));
    return Converters::toVertex(transfPoint);
}

gx::Vertex gx::Vertex::normalized() const
{
    double len = this->length();
    return *this / len;
}

gx::Vertex gx::Vertex::absolute() const
{
    return gx::Vertex(qAbs(m_x), qAbs(m_y));
}

gx::Vertex operator/(double scalar, const gx::Vertex& v)
{
    return gx::Vertex(scalar / v.x(), scalar / v.y());
}
