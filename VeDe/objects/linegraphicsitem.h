#ifndef LINEGRAPHICSITEM_H
#define LINEGRAPHICSITEM_H

#include "objects/basegraphicsitem.h"
#include "objects/line.h"

class LineGraphicsItem : public BaseGraphicsItem
{
public:
    LineGraphicsItem(std::shared_ptr<gx::Line> line);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
private:
    std::shared_ptr<gx::Line> m_line;
};

#endif // LINEGRAPHICSITEM_H
