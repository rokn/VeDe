#ifndef CANVASIMPL_H
#define CANVASIMPL_H

#include "canvas.h"

class CanvasWidget;

class CanvasImpl : public gx::Canvas
{
public:
    CanvasImpl(CanvasWidget* parent);
    CanvasImpl(CanvasWidget* parent, std::unique_ptr<gx::GObject> *root);
    void redraw();
    gx::Vertex getCursor() const;

private:
    CanvasWidget* m_parent;
};

#endif // CANVASIMPL_H
