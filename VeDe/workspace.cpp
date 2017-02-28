#include "workspace.h"
#include <QBrush>
#include <QDebug>
#include <QPalette>
#include <QPixmap>
#include <QWheelEvent>
#include <QTimeLine>
#include <QApplication>
#include <QScrollBar>

Workspace::Workspace(CanvasImpl *canvas, QWidget *parent)
    :QGraphicsView(parent)
{
    setMouseTracking(true);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
    setSceneRect(QRectF(-5000,-5000,10000,10000));
    m_pan = false;
    setCanvas(canvas);
    centerOn(-400 + canvas->getWidth() / 2, -300 + canvas->getHeight() / 2);
}

Workspace::~Workspace()
{
}

void Workspace::wheelEvent(QWheelEvent *event)
{
    if((event->modifiers() & Qt::ControlModifier) == Qt::ControlModifier)
    {
        handleZooming(event);
        event->accept();
        return;
    }
    event->ignore();
}

void Workspace::setCanvas(CanvasImpl *canvas)
{
    canvas->setBackgroundBrush(Qt::white);
    setFocusPolicy(Qt::WheelFocus);
    setScene(canvas);
    centerOn(canvas->getWidth() / 2, canvas->getHeight() / 2);
    m_canvas = canvas;
}

void Workspace::handleZooming(QWheelEvent *event)
{
    const QPointF p0scene = mapToScene(event->pos());

    qreal factor = std::pow(1.001, event->delta());
    scale(factor, factor);
    this->m_canvas->setZoomFactor(m_canvas->getZoomFactor() * factor);

    const QPointF p1mouse = mapFromScene(p0scene);
    const QPointF move = p1mouse - event->pos();
    horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
    verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());
}

void Workspace::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    if (m_pan)
    {
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - m_panStart.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - m_panStart.y()));
        m_panStart = QPoint(event->x(), event->y());
        m_canvas->redraw();
        event->accept();
        return;
    }

    event->ignore();
}

void Workspace::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if(event->button() == Qt::MiddleButton ||
            (event->button() == Qt::LeftButton && event->modifiers() & Qt::ControlModifier))
    {
        m_pan = true;
        m_panStart = QPoint(event->x(), event->y());
        setCursor(Qt::ClosedHandCursor);
        event->accept();
        return;
    }

    event->ignore();
}

void Workspace::mouseReleaseEvent(QMouseEvent *event)
{
    QGraphicsView::mouseReleaseEvent(event);

    if(event->button() == Qt::MiddleButton ||
            (event->button() == Qt::LeftButton && !(QApplication::mouseButtons() & Qt::MiddleButton)))
    {
        m_pan = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }

    event->ignore();
}
