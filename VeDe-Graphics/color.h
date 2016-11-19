#ifndef COLOR_H
#define COLOR_H

namespace gx
{
class Color
{
public:
    static Color fromRgba(int r, int g, int b, int a = 255);
public:
    Color();
    Color(int r, int g, int b, int a = 255);


private:
    int m_r;
    int m_g;
    int m_b;
    int m_a;
};
}

#endif // COLOR_H
