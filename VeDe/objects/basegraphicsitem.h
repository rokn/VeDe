#ifndef BASEGRAPHICSITEM_H
#define BASEGRAPHICSITEM_H

#include <QGraphicsItem>
#include "objects/gobject.h"

class BaseGraphicsItem : public QGraphicsItem
{
public:
    BaseGraphicsItem(std::shared_ptr<gx::GObject> object);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);

private:
    std::shared_ptr<gx::GObject> m_object;
};

#endif // BASEGRAPHICSITEM_H
