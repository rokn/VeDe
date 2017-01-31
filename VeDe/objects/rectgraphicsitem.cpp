#include "rectgraphicsitem.h"
#include "converters.h"
#include <QPainter>

RectGraphicsItem::RectGraphicsItem(std::shared_ptr<gx::Rectangle> rect)
    :BaseGraphicsItem(rect), m_rect(rect)
{

}

void RectGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseGraphicsItem::paint(painter,option,widget);

    QPointF p1, p2;
    p1 = gx::Converters::toPoint(m_rect->getTopLeft());
    p2 = gx::Converters::toPoint(m_rect->getBottomRight());
    QPen pen = painter->pen();
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);

    painter->drawRect(QRectF(p1,p2));
}
