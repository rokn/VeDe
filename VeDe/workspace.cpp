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
    :QGraphicsView(parent), m_canvas(canvas)
{
//    canvas->setBackgroundBrush(QBrush(QPixmap(":/images/grid.png")));
    canvas->setBackgroundBrush(Qt::white);
//    canvas->addItem(canvas);
//    canvas->grabMouse();
    setFocusPolicy(Qt::WheelFocus);
    setScene(canvas);
    setMouseTracking(true);
    setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    setRenderHints(QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
//    setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setSceneRect(QRectF(-5000,-5000,10000,10000));
    centerOn(0, 0);
//    translate(canvas->getWidth() / 2, canvas->getHeight() / 2);
//    rotate(90);
    m_pan = false;
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

void Workspace::handleZooming(QWheelEvent *event)
{
    const QPointF p0scene = mapToScene(event->pos());

    qreal factor = std::pow(1.001, event->delta());
    scale(factor, factor);
    this->m_canvas->setZoomFactor(m_canvas->getZoomFactor() * factor);

    const QPointF p1mouse = mapFromScene(p0scene);
    const QPointF move = p1mouse - event->pos(); // The move
    horizontalScrollBar()->setValue(move.x() + horizontalScrollBar()->value());
    verticalScrollBar()->setValue(move.y() + verticalScrollBar()->value());
    //    const int degrees = event->delta() / 8;
    //    int steps = degrees / 15;

    //    // Declare below as class member vars and set default values as below
    //    // qreal h11 = 1.0
    //    // qreal h12 = 0
    //    // qreal h21 = 1.0
    //    // qreal h22 = 0

    //    double scaleFactor = 1.0; //How fast we zoom
    //    const qreal minFactor = 1.0;
    //    const qreal maxFactor = 10.0;
    //    if(steps > 0)
    //    {
    //        h11 = (h11 >= maxFactor) ? h11 : (h11 + scaleFactor);
    //        h22 = (h22 >= maxFactor) ? h22 : (h22 + scaleFactor);
    //    }
    //    else
    //    {
    //        h11 = (h11 <= minFactor) ? minFactor : (h11 - scaleFactor);
    //        h22 = (h22 <= minFactor) ? minFactor : (h22 - scaleFactor);
    //    }

    //    this->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);
    //    this->setTransform(QTransform(h11, h12, h21, h22, 0, 0));
    //    QPoint  pos  = event->pos();
    //    QPointF posf = this->mapToScene(pos);

    //    double by;
    //    double angle = event->angleDelta().y();

    //    if      (angle > 0) { by = 1 + ( angle / 180 * 0.1); }
    //    else if (angle < 0) { by = 1 - (-angle / 180 * 0.1); }
    //    else                { by = 1; }

    //    this->scale(by, by);
    //    this->m_canvas->setZoomFactor(m_canvas->getZoomFactor() * by);

    //    double w = this->viewport()->width();
    //    double h = this->viewport()->height();

    //    double wf = this->mapToScene(QPoint(w-1, 0)).x()
    //                    - this->mapToScene(QPoint(0,0)).x();
    //    double hf = this->mapToScene(QPoint(0, h-1)).y()
    //                    - this->mapToScene(QPoint(0,0)).y();

    //    double lf = posf.x() - pos.x() * wf / w;
    //    double tf = posf.y() - pos.y() * hf / h;

    //    /* try to set viewport properly */
    //    this->ensureVisible(lf, tf, wf, hf, 0, 0);

    //    QPointF newPos = this->mapToScene(pos);

    //    /* readjust according to the still remaining offset/drift
    //     * I don't know how to do this any other way */
    //    this->ensureVisible(QRectF(QPointF(lf, tf) - newPos + posf,
    //                    QSizeF(wf, hf)), 0, 0);
}

void Workspace::mouseMoveEvent(QMouseEvent *event)
{
    QGraphicsView::mouseMoveEvent(event);

    if (m_pan)
    {
//        QPointF oldP = mapToScene(m_panStart);
//        QPointF newP = mapToScene(event->pos());
//        QPointF translation = newP - oldP;

//        translate(translation.x(), translation.y());

//        m_originX = event->x();
//        m_originY = event->y();
        horizontalScrollBar()->setValue(horizontalScrollBar()->value() - (event->x() - m_panStart.x()));
        verticalScrollBar()->setValue(verticalScrollBar()->value() - (event->y() - m_panStart.y()));
        m_panStart = QPoint(event->x(), event->y());
        m_canvas->redraw();
//        m_panStart = QPoint(event->x(), event->y());
        event->accept();
        return;
    }

    event->ignore();
}

void Workspace::mousePressEvent(QMouseEvent *event)
{
    QGraphicsView::mousePressEvent(event);

    if(event->button() == Qt::MiddleButton)
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

    if(event->button() == Qt::MiddleButton)
    {
        m_pan = false;
        setCursor(Qt::ArrowCursor);
        event->accept();
        return;
    }

    event->ignore();
}
