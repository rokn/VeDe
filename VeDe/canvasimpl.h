#ifndef CANVASIMPL_H
#define CANVASIMPL_H

#include "canvas.h"
#include "objects/gobject.h"
#include <QGraphicsScene>
#include <QMap>
#include <QSet>
#include <QGraphicsItem>

//class CanvasWidget;

class CanvasImpl : public QGraphicsScene, public gx::Canvas
{
    Q_OBJECT
public:
    CanvasImpl(QObject* parent, gx::SharedGObject root);
    static CanvasImpl* createCanvas(QObject* parent = 0, gx::SharedGObject root = 0);

    void mouseMoveEvent(QGraphicsSceneMouseEvent *event);
    void mousePressEvent(QGraphicsSceneMouseEvent *event);
    void mouseReleaseEvent(QGraphicsSceneMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);
    void redraw();
    void redrawGui();
    void redraw(QRectF area);
    gx::Vertex getCursor() const;
    bool isKeyPressed(Qt::Key key) const;
    void onAddObject(gx::SharedGObject object);

protected:
    void drawForeground(QPainter *painter, const QRectF &rect);

private:
    gx::Vertex m_mousePos;
    QMap<Qt::KeyboardModifier, bool> m_modifierKeys;
    QSet<Qt::Key> m_keys;

    void initModifierKeys();
    Qt::KeyboardModifier transformToMod(Qt::Key key);
    Qt::Key transformToKey(Qt::KeyboardModifier mod);
};

#endif // CANVASIMPL_H
