#include "pathgraphicsitem.h"
#include <QPainterPath>
#include <QPainter>
#include <QDebug>

PathGraphicsItem::PathGraphicsItem(std::shared_ptr<gx::Path> path)
    :BaseShapeItem(path), m_path(path)
{
}

void PathGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseShapeItem::paint(painter,option,widget);
    painter->drawPath(m_path->drawnPath());
//    painter->setBrush(QBrush(QColor(255,255,255,0)));
//    painter->drawRect(boundingRect());
}
