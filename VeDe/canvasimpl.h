#ifndef CANVASIMPL_H
#define CANVASIMPL_H

#include "canvas.h"
#include <QGraphicsItem>
#include <QMap>

class CanvasWidget;

class CanvasImpl : public gx::Canvas, public QGraphicsItem
{
    Q_OBJECT
public:
    CanvasImpl();
    CanvasImpl(std::shared_ptr<gx::GObject> root);
    static CanvasImpl* createCanvas(std::shared_ptr<gx::GObject> root = 0);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void redraw();
    gx::Vertex getCursor() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
private:
    gx::Vertex m_mousePos;
    QMap<Qt::KeyboardModifier, bool> m_modifierKeys;

    void initModifierKeys();
    Qt::KeyboardModifier transformToMod(Qt::Key key);
    Qt::Key transformToKey(Qt::KeyboardModifier mod);
};

#endif // CANVASIMPL_H
