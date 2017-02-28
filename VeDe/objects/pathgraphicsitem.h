#ifndef PATHGRAPHICSITEM_H
#define PATHGRAPHICSITEM_H

#include "baseshapeitem.h"
#include "objects/path.h"

class PathGraphicsItem : public BaseShapeItem
{
public:
    PathGraphicsItem(std::shared_ptr<gx::Path> path);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
private:
    std::shared_ptr<gx::Path> m_path;
};

#endif // PATHGRAPHICSITEM_H
