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
#include <QTransform>

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

    QRectF boundingBox() const;
    bool containsPoint(const gx::Vertex &point) const;

    bool isSelected() const;
    void setSelected(bool selected);

    const QTransform& getTransform() const;

    const QTransform& getTranslation() const;
    void setTranslation(const QTransform &translation);

    const QTransform& getRotation() const;
    void setRotation(const QTransform &rotation);

    const QTransform& getScale() const;
    void setScale(const QTransform &scale);

protected:
    void changed();
    void preChange();

    virtual QRectF shapeBoundingBox() const;
    virtual bool shapeContainsPoint(const gx::Vertex &point) const;

private:
    QList<std::shared_ptr<GObject>> m_children;
    std::shared_ptr<GObject> m_parent;
    Canvas* m_canvas;
    int m_zorder;
    unsigned int m_id;
    bool m_selected;
    QTransform m_transform;
    QTransform m_translation;
    QTransform m_rotation;
    QTransform m_scale;
    Event<const GObject*> m_onDestroy;
    Event<const GObject*> m_onPreChange;
    Event<const GObject*> m_onChange;

    void updateTransform();
};
}

#endif // GOBJECT_H
