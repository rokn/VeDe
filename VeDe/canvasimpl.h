#ifndef CANVASIMPL_H
#define CANVASIMPL_H

#include "canvas.h"
#include "objects/gobject.h"
#include <QGraphicsScene>
#include <QMap>
#include <QGraphicsItem>

//class CanvasWidget;

class CanvasImpl : public QGraphicsScene, public gx::Canvas
{
    Q_OBJECT
public:
    CanvasImpl(QObject* parent, std::shared_ptr<gx::GObject> root);
    static CanvasImpl* createCanvas(QObject* parent = 0, std::shared_ptr<gx::GObject> root = 0);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void redraw();
    gx::Vertex getCursor() const;
    void onAddObject(std::shared_ptr<gx::GObject> object);

//    QRectF boundingRect() const;
//    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
protected:
//    void drawBackground(QPainter *painter, const QRectF &rect);
    void drawItems(QPainter *painter, int numItems, QGraphicsItem *items[], const QStyleOptionGraphicsItem options[], QWidget *widget = Q_NULLPTR);

private:
    gx::Vertex m_mousePos;
    QMap<Qt::KeyboardModifier, bool> m_modifierKeys;

    void initModifierKeys();
    Qt::KeyboardModifier transformToMod(Qt::Key key);
    Qt::Key transformToKey(Qt::KeyboardModifier mod);
};

#endif // CANVASIMPL_H
