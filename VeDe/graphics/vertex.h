#ifndef VERTEX_H
#define VERTEX_H

#include <QPoint>

class Vertex
{
public:
    Vertex();
    Vertex(float x, float y);

    float getX() const;
    void setX(float x);

    float getY() const;
    void setY(float y);

    operator QPoint() const;

private:
    float _x;
    float _y;
};

#endif // VERTEX_H
