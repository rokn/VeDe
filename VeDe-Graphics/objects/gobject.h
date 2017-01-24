#ifndef GOBJECT_H
#define GOBJECT_H

#include <QMap>
#include <QString>
#include <QDebug>
#include "custompainter.h"
#include "properties/propertyholder.h"
#include <memory>
#include <functional>

namespace gx
{
class Canvas; //Forw. decl.


class GObject : public PropertyHolder
{
public:
    GObject(std::shared_ptr<GObject> parent = nullptr);
    virtual ~GObject();
    QList<std::shared_ptr<GObject> > &getChildren();
    void addChild(GObject *child, const std::shared_ptr<GObject> &parent);
    void addChild(std::shared_ptr<GObject> child, const std::shared_ptr<GObject> &parent);
    void paintAll(CustomPainter &painter);

    std::shared_ptr<GObject> getParent() const;
    void setParent(std::shared_ptr<GObject> parent);

    GObject *findInChildren(unsigned int id);

    unsigned int getId() const;
    void setId(unsigned int id);

    void forAllChildren(std::function<bool(GObject *)> action);

    void remove();
    void removeChild(unsigned int id);
    void removeAllChildren();

    Canvas *getCanvas() const;
    void setCanvas(Canvas *value);

    bool changedSinceDraw() const;

protected:
    virtual void paintSelf(CustomPainter& painter) = 0;
    void changed();

private:
    QList<std::shared_ptr<GObject>> m_children;
    std::shared_ptr<GObject> m_parent;
    Canvas* m_canvas;
    int m_zorder;
    unsigned int m_id;
    bool m_changedSinceDraw;
};
}

#endif // GOBJECT_H
