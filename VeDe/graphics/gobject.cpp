#include "gobject.h"

GObject::GObject()
{
    _properties.insert("stroke-color", new ColorProperty(QColor::fromRgb(0, 0, 0)));
}

//void GObject::paintEvent(QPaintEvent *event, QPaintDevice *device)
//{
//    drawSelf(event, device);

//    for(auto& child : _children)
//    {
//        child->paintEvent(event, device);
//    }
//}

void GObject::addChildren(std::shared_ptr<GObject> child)
{
    _children.append(child);
}
