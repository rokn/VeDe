#ifndef GOBJECT_H
#define GOBJECT_H

#include <QPaintEvent>
#include <QPainter>
#include <QMap>
#include <QString>
#include <typeinfo>
#include "graphics/colorproperty.h"

class GObject
{
public:
    explicit GObject();
//    void paintEvent(QPaintEvent *event, QPaintDevice *device);
    void addChildren(std::shared_ptr<GObject> child);

protected:
    virtual void drawSelf(QPaintEvent *event, QPaintDevice *device) = 0;

private:
    QMap<QString, Property*> _properties;
    QList<std::shared_ptr<GObject>> _children;


//Template Functions
public:
    template <typename T>
    T* getProp(QString propName)
    {
        auto res = _properties.find(propName);

        if(res != _properties.end())
        {
            return dynamic_cast<T*>(*res);
        }

        return Q_NULLPTR;
    }
};

#endif // GOBJECT_H
