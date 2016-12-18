#include "workspace.h"
#include <QBrush>
#include <QPalette>
#include <QPixmap>
#include <QWheelEvent>
#include <QTimeLine>

Workspace::Workspace(CanvasWidget *canvas, QWidget *parent)
    :QGraphicsView(parent), m_canvas(canvas)
{
    QGraphicsScene* scene = new QGraphicsScene(this);
    scene->setBackgroundBrush(QBrush(QPixmap(":/images/grid.png")));
    scene->addWidget(canvas);
    setDragMode(QGraphicsView::ScrollHandDrag);
    setFocusPolicy(Qt::WheelFocus);
    setScene(scene);
    setMouseTracking(true);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
}

Workspace::~Workspace()
{
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

void Workspace::wheelEvent(QWheelEvent *event)
{
    m_canvas->wheelEvent(event);

    if((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier)
    {
        handleZooming(event);
        event->accept();
    }
}

void Workspace::handleZooming(QWheelEvent *event)
{
    QPoint  pos  = event->pos();
    QPointF posf = this->mapToScene(pos);

    double by;
    double angle = event->angleDelta().y();

    if      (angle > 0) { by = 1 + ( angle / 180 * 0.1); }
    else if (angle < 0) { by = 1 - (-angle / 180 * 0.1); }
    else                { by = 1; }

    this->scale(by, by);

    double w = this->viewport()->width();
    double h = this->viewport()->height();

    double wf = this->mapToScene(QPoint(w-1, 0)).x()
                    - this->mapToScene(QPoint(0,0)).x();
    double hf = this->mapToScene(QPoint(0, h-1)).y()
                    - this->mapToScene(QPoint(0,0)).y();

    double lf = posf.x() - pos.x() * wf / w;
    double tf = posf.y() - pos.y() * hf / h;

    /* try to set viewport properly */
    this->ensureVisible(lf, tf, wf, hf, 0, 0);

    QPointF newPos = this->mapToScene(pos);

    /* readjust according to the still remaining offset/drift
     * I don't know how to do this any other way */
    this->ensureVisible(QRectF(QPointF(lf, tf) - newPos + posf,
                    QSizeF(wf, hf)), 0, 0);
}
