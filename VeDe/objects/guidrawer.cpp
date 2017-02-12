#include "guidrawer.h"
#include "qtcustompainter.h"
#include "tools/tool.h"
#include <QGraphicsScene>
#include <limits>

GUIDrawer::GUIDrawer()
{
    setZValue(std::numeric_limits<double>::max());
}

void GUIDrawer::setCanvas(gx::Canvas *canvas)
{
    m_canvas = canvas;
}

QRectF GUIDrawer::boundingRect() const
{
    return QRectF(-5000,-5000,10000,10000);
}

void GUIDrawer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QtCustomPainter customPainter(painter);

    if(m_canvas != nullptr)
    {
        m_canvas->getCurrTool()->drawGui(customPainter);
        auto selectedObjects = m_canvas->getSelectedObjects();

        if(selectedObjects.size() > 0)
        {
            QRectF unitedBox;
            painter->setBrush(QBrush(Qt::transparent));
            QPen selectPen(Qt::black);
            selectPen.setStyle(Qt::DashLine);
            selectPen.setWidthF(m_canvas->mapValueToZoom(1.0));
            painter->setPen(selectPen);

            foreach(auto& obj, selectedObjects) {
                painter->drawRect(obj->boundingBox());
                unitedBox = unitedBox.united(obj->boundingBox());
            }
            painter->drawRect(unitedBox);

        }
    }
}
