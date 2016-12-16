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
    QTransform matrix;
    matrix.scale(m_canvas->getCanvas()->getZoomFactor(), m_canvas->getCanvas()->getZoomFactor());
    setTransform(matrix);
//    scale(m_canvas->getCanvas()->getZoomFactor(), m_canvas->getCanvas()->getZoomFactor());

//    int numDegrees = event->angleDelta().y() / 8;
//    int numSteps = numDegrees / 15; // see QWheelEvent documentation
//    m_numScheduledScalings += numSteps;
//    if (m_numScheduledScalings * numSteps < 0) // if user moved the wheel in another direction, we reset previously scheduled scalings
//    m_numScheduledScalings = numSteps;

//    QTimeLine *anim = new QTimeLine(350, this);
//    anim->setUpdateInterval(20);

//    connect(anim, SIGNAL (valueChanged(qreal)), SLOT (scalingTime(qreal)));
//    connect(anim, SIGNAL (finished()), SLOT (animFinished()));
//    anim->start();
}

void Workspace::scalingTime(qreal x)
{
    qreal factor = qreal(m_numScheduledScalings) / 500.0;
    scale(factor,factor);
}

void Workspace::animFinished()
{
    if (m_numScheduledScalings > 0)
        m_numScheduledScalings--;
    else
        m_numScheduledScalings++;

    sender()->~QObject();
}
