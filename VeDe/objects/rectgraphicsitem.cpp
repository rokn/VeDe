#include "rectgraphicsitem.h"
#include "converters.h"
#include <QPainter>

RectGraphicsItem::RectGraphicsItem(std::shared_ptr<gx::Rectangle> rect)
    :BaseGraphicsItem(rect), m_rect(rect)
{

}

QRectF RectGraphicsItem::boundingRect() const
{
//    QPointF center = Converters::toPoint(m_ellipse->center());
//    QPointF radii = Converters::toPoint(m_ellipse->radius());
//    return QRectF(center - radii, center + radii);

    QPointF p1, p2;
    p1 = Converters::toPoint(m_rect->getTopLeft());
    p2 = Converters::toPoint(m_rect->getBottomRight());
    return QRectF(p1,p2);
}

void RectGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseGraphicsItem::paint(painter,option,widget);
    QPointF p1, p2;
    p1 = Converters::toPoint(m_rect->getTopLeft());
    p2 = Converters::toPoint(m_rect->getBottomRight());
    QPen pen = painter->pen();
    pen.setJoinStyle(Qt::MiterJoin);
    painter->setPen(pen);
    painter->drawRect(QRectF(p1,p2));
}
