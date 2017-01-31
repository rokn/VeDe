#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QGraphicsView>
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include "canvasimpl.h"

class Workspace : public QGraphicsView
{

    Q_OBJECT
public:
    Workspace(CanvasImpl *canvas, QWidget *parent = nullptr);
    ~Workspace();

    void wheelEvent(QWheelEvent *event);

private:
    CanvasImpl* m_canvas;
    int m_numScheduledScalings;

    void handleZooming(QWheelEvent *event);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

    bool m_pan;
    QPoint m_panStart;
};


#endif // WORKSPACE_H
