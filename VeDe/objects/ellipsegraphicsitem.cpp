#include "ellipsegraphicsitem.h"
#include "converters.h"
#include <QPainter>

EllipseGraphicsItem::EllipseGraphicsItem(std::shared_ptr<gx::Ellipse> ellipse)
    :BaseGraphicsItem(ellipse), m_ellipse(ellipse)
{
}

QRectF EllipseGraphicsItem::boundingRect() const
{
    QPointF center = Converters::toPoint(m_ellipse->center());
    QPointF radii = Converters::toPoint(m_ellipse->radius());
    return QRectF(center - radii, center + radii);
}

void EllipseGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseGraphicsItem::paint(painter,option,widget);
    painter->drawEllipse(Converters::toPoint(m_ellipse->center()), m_ellipse->radius().x(), m_ellipse->radius().y());
    painter->setBrush(QBrush(QColor(255,255,255,0)));
//    painter->drawRect(boundingRect());
    painter->drawRect(sceneBoundingRect());
}
