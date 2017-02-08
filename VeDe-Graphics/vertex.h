#ifndef VERTEX_H
#define VERTEX_H

namespace gx
{
class Vertex
{
public:
    Vertex();
    Vertex(const Vertex& other);
    Vertex(float x, float y);

    float x() const;
    void setX(float x);

    float y() const;
    void setY(float y);

    Vertex& operator +=(const Vertex& other);
    Vertex& operator -=(const Vertex& other);

    Vertex operator +(const Vertex& other) const;
    Vertex operator -(const Vertex& other) const;
    float operator *(const Vertex& other) const;

    Vertex& operator +=(float& scalar);
    Vertex& operator -=(float& scalar);
    Vertex& operator *=(float& scalar);
    Vertex& operator /=(float& scalar);

    Vertex operator +(float& scalar) const;
    Vertex operator -(float& scalar) const;
    Vertex operator *(float& scalar) const;
    Vertex operator /(float& scalar) const;

    float distance(const Vertex& other) const;
    float length() const;
    float lengthSquared() const;

private:
    float m_x;
    float m_y;
};
}

#endif // VERTEX_H
