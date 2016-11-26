#include "canvaswidget.h"
#include "objects/ellipse.h"
#include "tools/transition.h"
#include <QMouseEvent>

CanvasWidget::CanvasWidget(QWidget *parent)
    :QWidget(parent), Canvas()
{
}

CanvasWidget::CanvasWidget(std::unique_ptr<gx::GObject> *root, QWidget *parent)
    :QWidget(parent), Canvas(root)
{
}

CanvasWidget* CanvasWidget::createCanvasWidget(QWidget *parent, std::unique_ptr<gx::GObject> *root)
{
    CanvasWidget* widget = nullptr;
    if(root == nullptr)
    {
        widget = new CanvasWidget(parent);
    }
    else
    {
        widget = new CanvasWidget(root, parent);
    }

    widget->setMouseTracking(true);
    widget->setFocusPolicy(Qt::WheelFocus);
    return widget;
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    if(root() != nullptr)
    {
        QtCustomPainter painter(this);
        this->root()->paintAll(painter);
    }
}

void CanvasWidget::redraw()
{
    update();
}

gx::Vertex CanvasWidget::getCursor() const
{
    QPoint relativePos = this->mapFromGlobal(QCursor::pos());
    return gx::Vertex(relativePos.x(), relativePos.y());
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    gx::Transition transition(event->type(), event->button());
    handleEvent(transition);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    gx::Transition transition(event->type(), event->button());
    handleEvent(transition);
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    gx::Transition transition(event->type(), event->button());
    handleEvent(transition);
}

void CanvasWidget::keyPressEvent(QKeyEvent *event)
{
    gx::Transition transition(event->type(), (Qt::Key)event->key());
    handleEvent(transition);
}

void CanvasWidget::keyReleaseEvent(QKeyEvent *event)
{
    gx::Transition transition(event->type(), (Qt::Key)event->key());
    handleEvent(transition);
}
