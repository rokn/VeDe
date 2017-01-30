#ifndef PATHGRAPHICSITEM_H
#define PATHGRAPHICSITEM_H

#include "basegraphicsitem.h"
#include "objects/path.h"

class PathGraphicsItem : public BaseGraphicsItem
{
public:
    PathGraphicsItem(std::shared_ptr<gx::Path> path);

    QRectF boundingRect() const;

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
private:
    QPainterPath m_drawnPath;
    std::shared_ptr<gx::Path> m_path;

    void constructPath();
};

#endif // PATHGRAPHICSITEM_H
