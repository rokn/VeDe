#ifndef LINEGRAPHICSITEM_H
#define LINEGRAPHICSITEM_H

#include "objects/basegraphicsitem.h"
#include "objects/line.h"

class LineGraphicsItem : public BaseShapeItem
{
public:
    LineGraphicsItem(std::shared_ptr<gx::Line> line);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
private:
    std::shared_ptr<gx::Line> m_line;
};

#endif // LINEGRAPHICSITEM_H
