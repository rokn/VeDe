#ifndef RECTGRAPHICSITEM_H
#define RECTGRAPHICSITEM_H

#include "objects/baseshapeitem.h"
#include "objects/rectangle.h"

class RectGraphicsItem : public BaseShapeItem
{
public:
    RectGraphicsItem(std::shared_ptr<gx::Rectangle> rect);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
private:
    std::shared_ptr<gx::Rectangle> m_rect;
};

#endif // RECTGRAPHICSITEM_H
