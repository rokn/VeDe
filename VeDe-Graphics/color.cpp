#include "color.h"

gx::Color gx::Color::fromRgba(int r, int g, int b, int a)
{
    return Color(r,g,b,a);
}

gx::Color::Color()
    :Color(0, 0, 0, 0)
{
}

gx::Color::Color(int r, int g, int b, int a)
    :m_r(r), m_g(g), m_b(b), m_a(a)
{
}
