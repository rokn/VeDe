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

private:
    float m_x;
    float m_y;
};
}

#endif // VERTEX_H
