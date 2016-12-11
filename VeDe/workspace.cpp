#include "workspace.h"
#include <QBrush>
#include <QPalette>
#include <QPixmap>

Workspace::Workspace(CanvasWidget *canvas, QWidget *parent)
    :QGraphicsView(parent), m_canvas(canvas)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QPixmap(":/images/grid.png")));
    scene->addWidget(canvas);
    setScene(scene);
    setMouseTracking(true);
}

void Workspace::mouseMoveEvent(QMouseEvent *event)
{
    m_canvas->mouseMoveEvent(event);
}

void Workspace::mousePressEvent(QMouseEvent *event)
{
    m_canvas->mousePressEvent(event);
}

void Workspace::mouseReleaseEvent(QMouseEvent *event)
{
    m_canvas->mouseReleaseEvent(event);
}

void Workspace::keyPressEvent(QKeyEvent *event)
{
    m_canvas->keyPressEvent(event);
}

void Workspace::keyReleaseEvent(QKeyEvent *event)
{
    m_canvas->keyReleaseEvent(event);
}
