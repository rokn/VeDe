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
    GObject(std::shared_ptr<GObject> parent = nullptr);
    virtual ~GObject();
    QList<std::shared_ptr<GObject> > &getChildren();
    void addChild(GObject *child);
    void addChild(std::shared_ptr<GObject> child);
    void paintAll(CustomPainter &painter) const;

    std::shared_ptr<GObject> getParent() const;
    void setParent(const std::shared_ptr<GObject> &parent);

protected:
    virtual void paintSelf(CustomPainter& painter) const = 0;

private:
    QList<std::shared_ptr<GObject>> m_children;
    std::shared_ptr<GObject> m_parent;
    int m_zorder;
};
}

#endif // GOBJECT_H
