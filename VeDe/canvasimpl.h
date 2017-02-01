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
    void redrawGui();
    void redraw(QRectF area);
    gx::Vertex getCursor() const;
    void onAddObject(std::shared_ptr<gx::GObject> object);

protected:
    void drawForeground(QPainter *painter, const QRectF &rect);

private:
    gx::Vertex m_mousePos;
    QMap<Qt::KeyboardModifier, bool> m_modifierKeys;

    void initModifierKeys();
    Qt::KeyboardModifier transformToMod(Qt::Key key);
    Qt::Key transformToKey(Qt::KeyboardModifier mod);
};

#endif // CANVASIMPL_H
