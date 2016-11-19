#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{
}

CanvasWidget::CanvasWidget(std::unique_ptr<gx::GObject> &root, QWidget *parent)
    :QWidget(parent), Canvas(root)
{
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    if(root() != nullptr)
    {
        QtCustomPainter painter(this);
        this->root()->paintAll(painter);
    }
}

gx::Vertex CanvasWidget::getCursor() const
{
    QPoint relativePos = this->mapFromGlobal(QCursor::pos());
    return gx::Vertex(relativePos.x(), relativePos.y());
}

