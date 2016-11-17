#include "canvaswidget.h"

CanvasWidget::CanvasWidget(QWidget *parent) : QWidget(parent)
{

}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    _root.paintEvent(event, this);
}

