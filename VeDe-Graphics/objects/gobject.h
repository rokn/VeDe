#ifndef GOBJECT_H
#define GOBJECT_H

#include <QMap>
#include <QString>
#include <QDebug>
#include "custompainter.h"
#include "properties/propertyholder.h"
#include <memory>

namespace gx
{
class GObject : public PropertyHolder
{
public:
    GObject();
    virtual ~GObject();
    QList<std::shared_ptr<GObject> > &getChildren();
    void addChildren(GObject *child);
    void addChildren(std::shared_ptr<GObject> child);
    void paintAll(CustomPainter &painter) const;

protected:
    virtual void paintSelf(CustomPainter& painter) const = 0;

private:
    QList<std::shared_ptr<GObject>> m_children;
    int m_zorder;


//Template Functions
public:
//    template <typename T>
//    T* getProp(QString propName)
//    {
//        auto res = m_properties.find(propName);
//
//        if(res != m_properties.end())
//        {
//            return dynamic_cast<T*>(*res);
//        }
//
//        return Q_NULLPTR;
    //    }
};
}

#endif // GOBJECT_H
