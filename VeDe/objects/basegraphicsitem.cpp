#include "basegraphicsitem.h"
#include "converters.h"
#include "objects/gobject.h"
#include "canvas.h"
#include "properties/propertynames.h"
#include <QPainter>
#include <QPointF>
#include <QGraphicsScene>
#include <QTransform>

BaseShapeItem::BaseShapeItem(std::shared_ptr<gx::Shape> object)
    :m_object(object)
{

    m_object->onPreChange() += [this](const gx::GObject* o){
        this->prepareGeometryChange();
    };
}

QRectF BaseShapeItem::boundingRect() const
{
    return m_object->boundingBox();
}

void BaseShapeItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{

    if(!m_object->isGuiElement())
    {
        painter->setClipping(true);
        float canvasWidth = m_object->getCanvas()->getWidth();
        float canvasHeight = m_object->getCanvas()->getHeight();
        painter->setClipRect(QRectF( 0.5,  0.5, canvasWidth - 1, canvasHeight - 1)); // Fix for canvas border
    }

    painter->setTransform(painter->transform() * m_object->getTransform());
    painter->setBrush(QBrush(gx::Converters::toQColor(m_object->getProp(gx::PROP::BACK_COLOR)->toColor())));
    QPen pen(gx::Converters::toQColor(m_object->getProp(gx::PROP::STROKE_COLOR)->toColor()));
    pen.setWidthF(m_object->getProp(gx::PROP::STROKE_WIDTH)->toFloat());
    painter->setPen(pen);
}



