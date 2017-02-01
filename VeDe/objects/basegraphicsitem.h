#ifndef BASEGRAPHICSITEM_H
#define BASEGRAPHICSITEM_H

#include <QGraphicsItem>
#include <memory>
#include "objects/shape.h"

class BaseGraphicsItem : public QGraphicsItem
{
public:
    BaseGraphicsItem(std::shared_ptr<gx::Shape> object);

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

private:
    std::shared_ptr<gx::Shape> m_object;
};

#endif // BASEGRAPHICSITEM_H
