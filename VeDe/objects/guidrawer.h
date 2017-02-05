#ifndef GUIDRAWER_H
#define GUIDRAWER_H

#include <QGraphicsItem>
#include "tools/tool.h"

class GUIDrawer : public QGraphicsItem
{
public:
    GUIDrawer();
    void setTool(gx::Tool *tool);
    gx::Tool *getTool() const;

    QRectF boundingRect() const;
    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);


private:
    gx::Tool* m_tool;
};

#endif // GUIDRAWER_H
