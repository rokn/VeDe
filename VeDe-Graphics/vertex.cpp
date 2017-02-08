#include "vertex.h"
#include <QtMath>

gx::Vertex::Vertex()
    :m_x(0.0f), m_y(0.0f)
{
}

gx::Vertex::Vertex(const Vertex &other)
    :m_x(other.x()), m_y(other.y())
{
}

gx::Vertex::Vertex(float x, float y)
    :m_x(x), m_y(y)
{
}

float gx::Vertex::x() const
{
    return m_x;
}

void gx::Vertex::setX(float x)
{
    m_x = x;
}

float gx::Vertex::y() const
{
    return m_y;
}

void gx::Vertex::setY(float y)
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

float gx::Vertex::operator *(const gx::Vertex &other) const
{
    return m_x * other.x() + m_y * other.y();
}

gx::Vertex &gx::Vertex::operator +=(float &scalar)
{
    this->m_x += scalar;
    this->m_y += scalar;
    return *this;
}

gx::Vertex &gx::Vertex::operator -=(float &scalar)
{
    this->m_x -= scalar;
    this->m_y -= scalar;
    return *this;
}

gx::Vertex &gx::Vertex::operator *=(float &scalar)
{
    this->m_x *= scalar;
    this->m_y *= scalar;
    return *this;
}

gx::Vertex &gx::Vertex::operator /=(float &scalar)
{
    this->m_x /= scalar;
    this->m_y /= scalar;
    return *this;
}

gx::Vertex gx::Vertex::operator +(float &scalar) const
{
    return Vertex(m_x + scalar, m_y + scalar);
}

gx::Vertex gx::Vertex::operator -(float &scalar) const
{
    return Vertex(m_x - scalar, m_y - scalar);
}

gx::Vertex gx::Vertex::operator *(float &scalar) const
{
    return Vertex(m_x * scalar, m_y * scalar);
}

gx::Vertex gx::Vertex::operator /(float &scalar) const
{
    return Vertex(m_x / scalar, m_y / scalar);
}

float gx::Vertex::distance(const gx::Vertex &other) const
{
    return qSqrt(qPow(other.x() - m_x, 2) + qPow(other.y() - m_y, 2));
}

float gx::Vertex::length() const
{
    return qSqrt(qPow(m_x, 2) + qPow(m_y, 2));
}

float gx::Vertex::lengthSquared() const
{
    return qPow(m_x, 2) + qPow(m_y, 2);
}
