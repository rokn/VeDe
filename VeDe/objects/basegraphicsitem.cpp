#include "basegraphicsitem.h"
#include "converters.h"
#include "canvas.h"
#include "properties/propertynames.h"
#include <QPainter>
#include <QPointF>
#include <QGraphicsScene>

BaseGraphicsItem::BaseGraphicsItem(std::shared_ptr<gx::Shape> object)
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
    if(m_object->isGuiElement() && m_object->getCanvas() != nullptr)
    {
        m_object->getProp(gx::PROP::STROKE_WIDTH)->toFloat() = 1.0f / m_object->getCanvas()->getZoomFactor(); // Get this to an event of changing zoom
    }

#if DEBUG
    painter->setBrush(QBrush(QColor(0,0,0,0)));
    QPen debugPen(QColor(255,0,0,255));
    debugPen.setWidthF(1.0f / m_object->getCanvas()->getZoomFactor());
    painter->setPen(debugPen);
    painter->drawRect(boundingRect());
#endif

    painter->setBrush(QBrush(gx::Converters::toQColor(m_object->getProp(gx::PROP::BACK_COLOR)->toColor())));
    QPen pen(gx::Converters::toQColor(m_object->getProp(gx::PROP::STROKE_COLOR)->toColor()));
    pen.setWidthF(m_object->getProp(gx::PROP::STROKE_WIDTH)->toFloat());
    painter->setPen(pen);

}



