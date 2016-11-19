#include "canvaswidget.h"
#include "graphics/line.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    QtCustomPainter painter(this);
    this->root()->paintAll(painter);
}

gx::Vertex CanvasWidget::getCursor() const
{
    QPoint relativePos = this->mapFromGlobal(QCursor::pos());
    return gx::Vertex(relativePos.x(), relativePos.y());
}

