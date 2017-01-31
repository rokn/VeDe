#ifndef SHAPE_H
#define SHAPE_H

#include "gobject.h"

namespace gx
{
class Shape : public GObject
{
public:
    Shape();

    bool isGuiElement() const;
    void setGuiElement(bool guiElement);

protected:
    void paintSelf(CustomPainter& painter);

private:
    bool m_guiElement;
};
}

#endif // SHAPE_H
