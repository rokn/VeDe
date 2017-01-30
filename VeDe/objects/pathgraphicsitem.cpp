#include "pathgraphicsitem.h"
#include "converters.h"
#include <QPainterPath>
#include <QPainter>
#include <QDebug>

PathGraphicsItem::PathGraphicsItem(std::shared_ptr<gx::Path> path)
    :BaseGraphicsItem(path), m_path(path)
{
    m_path->onChange([this](const gx::GObject* o){
        this->constructPath();
    });

    this->constructPath();
}

QRectF PathGraphicsItem::boundingRect() const
{
    return m_drawnPath.boundingRect();
}

void PathGraphicsItem::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    BaseGraphicsItem::paint(painter,option,widget);
    painter->drawPath(m_drawnPath);
    painter->setBrush(QBrush(QColor(255,255,255,0)));
    painter->drawRect(boundingRect());
}

void PathGraphicsItem::constructPath()
{
    m_drawnPath = QPainterPath();
    QList<gx::Vertex> vertices = m_path->vertices();
    QList<bool> controls = m_path->controls();
    m_drawnPath.setFillRule(Qt::WindingFill);
    QPointF curr, prev, control1, control2;
    bool hasControl1 = controls[0], hasControl2 = false;
    int vIndex = (hasControl1) ? 2 : 1;
    control1 = Converters::toPoint(vertices[vIndex - 1]);

    prev = Converters::toPoint(vertices[0]);
    m_drawnPath.moveTo(prev);


    for (auto control = controls.begin() + 1; control != controls.end(); ++control) {
        curr = Converters::toPoint(vertices[vIndex]);
        hasControl2 = *control;
        if(hasControl2) {
            control2 = 2 * curr - Converters::toPoint(vertices[vIndex+1]);
        } else {
            control2 = curr;
        }

        if(hasControl1 || hasControl2){
            m_drawnPath.cubicTo(control1, control2, curr);
        } else {
            m_drawnPath.lineTo(curr);
        }

        hasControl1 = hasControl2;
        control1 = control2;
        prev = curr;

        if(hasControl2) {
            vIndex += 2;
            control1 = 2 * curr - control1;
        } else {
            vIndex ++;
        }
    }
}
