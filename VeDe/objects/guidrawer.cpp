#include "guidrawer.h"
#include "qtcustompainter.h"

GUIDrawer::GUIDrawer()
{

}

void GUIDrawer::setTool(gx::Tool *tool)
{
    m_tool = tool;
}

gx::Tool *GUIDrawer::getTool() const
{
    return m_tool;
}

void GUIDrawer::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    QtCustomPainter customPainter(painter);

    if(m_tool != nullptr)
    {
        m_tool->drawGui(customPainter);
    }
}
