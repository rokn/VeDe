#ifndef ELLIPSEGRAPHICSITEM_H
#define ELLIPSEGRAPHICSITEM_H

#include "objects/baseshapeitem.h"
#include "objects/ellipse.h"

class EllipseGraphicsItem : public BaseShapeItem
{
public:
    EllipseGraphicsItem(std::shared_ptr<gx::Ellipse> ellipse);

    void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
private:
    std::shared_ptr<gx::Ellipse> m_ellipse;
};

#endif // ELLIPSEGRAPHICSITEM_H
