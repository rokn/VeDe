#include "guidrawer.h"
#include "qtcustompainter.h"
#include <QGraphicsScene>
#include <limits>

GUIDrawer::GUIDrawer()
{
    setZValue(std::numeric_limits<double>::max());
}

void GUIDrawer::setTool(gx::Tool *tool)
{
    m_tool = tool;
}

gx::Tool *GUIDrawer::getTool() const
{
    return m_tool;
}

QRectF GUIDrawer::boundingRect() const
{
    return QRectF(-5000,-5000,10000,10000);
}

void GUIDrawer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QtCustomPainter customPainter(painter);

    if(m_tool != nullptr)
    {
        m_tool->drawGui(customPainter);
    }
}
