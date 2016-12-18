#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QGraphicsView>
#include "canvaswidget.h"

class Workspace : public QGraphicsView
{
    Q_OBJECT
public:
    Workspace(CanvasWidget* canvas, QWidget *parent = nullptr);
    ~Workspace();

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void wheelEvent(QWheelEvent *event);

private:
    CanvasWidget* m_canvas;
    int m_numScheduledScalings;

    void handleZooming(QWheelEvent *event);
};

#endif // WORKSPACE_H
