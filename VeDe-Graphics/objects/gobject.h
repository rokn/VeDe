#ifndef GOBJECT_H
#define GOBJECT_H

#include <QMap>
#include <QString>
#include <QDebug>
#include "custompainter.h"
#include "event.h"
#include "properties/propertyholder.h"
#include <memory>
#include <functional>
#include <QRectF>

namespace gx
{
class Canvas; //Forw. decl.


class GObject : public PropertyHolder
{
//    typedef std::function<void(const GObject*)> GobjectCallback;

public:
    GObject(std::shared_ptr<GObject> parent = nullptr);
    virtual ~GObject();
    QList<std::shared_ptr<GObject> > &getChildren();
    void addChild(GObject *child, const std::shared_ptr<GObject> &parent);
    void addChild(std::shared_ptr<GObject> child, const std::shared_ptr<GObject> &parent);

    std::shared_ptr<GObject> getParent() const;
    void setParent(std::shared_ptr<GObject> parent);

    GObject *findInChildren(unsigned int id);

    unsigned int getId() const;
    void setId(unsigned int id);

    void forAllChildren(std::function<bool(GObject *)> action);

    Event<const GObject*> &onDestroy();
    Event<const GObject*> &onPreChange();
    Event<const GObject*> &onChange();

    void remove();
    void removeChild(unsigned int id);
    void removeAllChildren();

    Canvas *getCanvas() const;
    void setCanvas(Canvas *value);

    void preparePropertyChange();
    void updateProperties();

    virtual QRectF boundingBox() const;

    bool isSelected() const;
    void setSelected(bool selected);

protected:
    void changed();
    void preChange();

private:
    QList<std::shared_ptr<GObject>> m_children;
    std::shared_ptr<GObject> m_parent;
    Canvas* m_canvas;
    int m_zorder;
    unsigned int m_id;
    bool m_selected;
//    QList<GobjectCallback> m_onDestroyCallbacks;
//    QList<GobjectCallback> m_onPreChangeCallbacks;
//    QList<GobjectCallback> m_onChangeCallbacks;
    Event<const GObject*> m_onDestroy;
    Event<const GObject*> m_onPreChange;
    Event<const GObject*> m_onChange;
};
}

#endif // GOBJECT_H
