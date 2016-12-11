#ifndef WORKSPACE_H
#define WORKSPACE_H

#include <QGraphicsView>
#include "canvaswidget.h"

class Workspace : public QGraphicsView
{
public:
    Workspace(CanvasWidget* canvas, QWidget *parent = nullptr);

    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
private:
    CanvasWidget* m_canvas;
};

#endif // WORKSPACE_H
