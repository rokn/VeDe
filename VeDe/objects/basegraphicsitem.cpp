#include "basegraphicsitem.h"
#include "converters.h"
#include "properties/propertynames.h"
#include <QPainter>
#include <QPointF>
#include <QGraphicsScene>

BaseGraphicsItem::BaseGraphicsItem(std::shared_ptr<gx::GObject> object)
    :m_object(object)
{
    m_object->onDestroy([this](const gx::GObject* o)
    {
        this->scene()->removeItem(this);
    });

    m_object->onPreChange([this](const gx::GObject* o){
        this->prepareGeometryChange();
    });
}

QRectF BaseGraphicsItem::boundingRect() const
{
    return m_object->boundingBox();
}

void BaseGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    painter->setBrush(QBrush(gx::Converters::toQColor(m_object->getProp(gx::PROP::BACK_COLOR)->toColor())));
    QPen pen(gx::Converters::toQColor(m_object->getProp(gx::PROP::STROKE_COLOR)->toColor()));
    pen.setWidthF(m_object->getProp(gx::PROP::STROKE_WIDTH)->toFloat());
    painter->setPen(pen);
}



