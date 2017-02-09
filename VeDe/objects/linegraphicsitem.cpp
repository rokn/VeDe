#include "linegraphicsitem.h"
#include "converters.h"
#include <QtMath>
#include <QPainter>

LineGraphicsItem::LineGraphicsItem(std::shared_ptr<gx::Line> line)
    :BaseShapeItem(line), m_line(line)
{

}

void LineGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseShapeItem::paint(painter,option,widget);
    QPointF p1, p2;
    p1 = gx::Converters::toPoint(m_line->start());
    p2 = gx::Converters::toPoint(m_line->end());
    painter->drawLine(p1,p2);
//    painter->setBrush(QBrush(QColor(255,255,255,0)));
//    painter->drawRect(boundingRect());
}
