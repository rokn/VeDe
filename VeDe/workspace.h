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
    bool eventFilter(QObject* o,QEvent* e);

private:
    CanvasImpl* m_canvas;
    int m_numScheduledScalings;

    void handleZooming(QWheelEvent *event);
};

class WorkspaceScene :public QGraphicsScene
{
    Q_OBJECT
public:
    WorkspaceScene(CanvasImpl* canvas, QObject* parent=0)
        :QGraphicsScene(parent), m_canvas(canvas){}
//    void mouseMoveEvent(QGraphicsSceneMouseEvent *event)
//    {
//        qDebug() << "Original : " << event->pos();
//        event->setPos(m_canvas->mapFromScene(event->pos()));
//        qDebug() << "Mapped : " << event->pos();
//        m_canvas->mouseMoveEvent(event);
//    }
    bool eventFilter(QObject* o,QEvent* e){

        if(e->type() == QEvent::KeyPress) {
            qWarning() << "The guy which steals the keyevent is" << o;
            WorkspaceScene *scene = (WorkspaceScene*)o;
            QKeyEvent *event = (QKeyEvent*)e;
            qWarning() << scene << event;
        }
    }

private:
    CanvasImpl* m_canvas;
};

#endif // WORKSPACE_H
