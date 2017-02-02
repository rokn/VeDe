#ifndef SHAPE_H
#define SHAPE_H

#include "gobject.h"
#include "common.h"

namespace gx
{
class Shape : public GObject
{
public:
    Shape();
    ~Shape();

    bool isGuiElement() const;
    void setGuiElement(bool guiElement);

protected:
    void fixBoxForStrokeWidth(QRectF& rect, float factor=0.5f) const;
private:
    bool m_guiElement;
    uint m_canvasZoomHandlerId;

    void onCanvasZoomChange(float zoomFactor);
};
}

#endif // SHAPE_H
