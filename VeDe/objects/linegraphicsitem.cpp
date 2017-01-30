#include "linegraphicsitem.h"
#include "converters.h"
#include <QtMath>
#include <QPainter>

LineGraphicsItem::LineGraphicsItem(std::shared_ptr<gx::Line> line)
    :BaseGraphicsItem(line), m_line(line)
{

}

QRectF LineGraphicsItem::boundingRect() const
{
//    QPointF center = Converters::toPoint(m_ellipse->center());
//    QPointF radii = Converters::toPoint(m_ellipse->radius());
//    return QRectF(center - radii, center + radii);
    QPointF p1, p2;
    p1 = Converters::toPoint(m_line->start());
    p2 = Converters::toPoint(m_line->end());
    QPointF tl,dr;
    tl.setX(qMin(p1.x(), p2.x()));
    tl.setY(qMin(p1.y(), p2.y()));
    dr.setX(qMax(p1.x(), p2.x()));
    dr.setY(qMax(p1.y(), p2.y()));
    return QRectF(tl,dr);
}

void LineGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseGraphicsItem::paint(painter,option,widget);
    QPointF p1, p2;
    p1 = Converters::toPoint(m_line->start());
    p2 = Converters::toPoint(m_line->end());
    painter->drawLine(p1,p2);
    painter->setBrush(QBrush(QColor(255,255,255,0)));
    painter->drawRect(boundingRect());
}
