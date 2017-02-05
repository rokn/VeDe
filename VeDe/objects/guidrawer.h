#ifndef GUIDRAWER_H
#define GUIDRAWER_H

#include <QGraphicsItem>
#include "canvas.h"

class GUIDrawer : public QGraphicsItem
{
public:
    GUIDrawer();
    void setCanvas(gx::Canvas *canvas);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);


private:
    gx::Canvas* m_canvas;
};

#endif // GUIDRAWER_H
