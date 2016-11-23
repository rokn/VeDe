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

int gx::Color::a() const
{
    return m_a;
}

int gx::Color::b() const
{
    return m_b;
}

int gx::Color::g() const
{
    return m_g;
}

int gx::Color::r() const
{
    return m_r;
}
