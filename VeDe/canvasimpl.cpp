#include "canvasimpl.h"
#include "canvaswidget.h"

CanvasImpl::CanvasImpl(CanvasWidget *parent)
    :m_parent(parent)
{
    setParent(parent);
}
//TODO: Rework
CanvasImpl::CanvasImpl(CanvasWidget *parent, std::unique_ptr<gx::GObject> *root)
    :gx::Canvas(root), m_parent(parent)
{
    setParent(parent);
}

void CanvasImpl::redraw()
{
    m_parent->update();
}

gx::Vertex CanvasImpl::getCursor() const
{
    QPoint relativePos = m_parent->mapFromGlobal(QCursor::pos());
    return gx::Vertex(relativePos.x(), relativePos.y());
}
