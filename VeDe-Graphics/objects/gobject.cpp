#include "gobject.h"
#include "helpers.h"
#include "canvas.h"
#include "graphics_exceptions.h"
#include <QStack>
#include <QDebug>

gx::GObject::GObject(std::shared_ptr<gx::GObject> parent)
{
    if(parent != nullptr)
    {
        parent->addChild(this, parent);
    }
    m_canvas = nullptr;
}

gx::GObject::~GObject()
{
}

void gx::GObject::addChild(gx::GObject *child, const std::shared_ptr<GObject>& parent)
{
    std::shared_ptr<gx::GObject> ch(child);
    addChild(ch, parent);
}

QList<std::shared_ptr<gx::GObject>>& gx::GObject::getChildren()
{
    return m_children;
}

void gx::GObject::addChild(std::shared_ptr<GObject> child, const std::shared_ptr<GObject>& parent)
{
    child->setParent(parent);
    this->m_children.append(child);
}

std::shared_ptr<gx::GObject> gx::GObject::getParent() const
{
    return m_parent;
}

void gx::GObject::setParent(std::shared_ptr<GObject> parent)
{
    m_parent = parent;
}

gx::GObject *gx::GObject::findInChildren(unsigned int id)
{
    gx::GObject* child = nullptr;
    forAllChildren([&](GObject* c){
        if(c->m_id == id) {
            child = c;
            return true;
        }
        return false;
    });

    return child;
}

void gx::GObject::forAllChildren(std::function<bool (gx::GObject *)> action)
{
    QStack<GObject*> stack;
    GObject* curr;
    stack.push_back(this);

    while(!stack.isEmpty())
    {
        curr = stack.back();
        stack.pop_back();

        if(action(curr)) break;

        auto it = curr->m_children.end();

        while(it != curr->m_children.begin())
        {
            it--;
            stack.push_back((*it).get());
        }
    }
}

void gx::GObject::onDestroy(gx::GObject::GobjectCallback callback)
{
    m_onDestroyCallbacks.append(callback);
}

void gx::GObject::onPreChange(gx::GObject::GobjectCallback callback)
{
    m_onPreChangeCallbacks.append(callback);
}

void gx::GObject::onChange(gx::GObject::GobjectCallback callback)
{
    m_onChangeCallbacks.append(callback);
}

void gx::GObject::remove()
{
    m_parent->removeChild(m_id);
}

void gx::GObject::removeChild(unsigned int id)
{
    auto childIt= m_children.begin();

    while(childIt != m_children.end())
    {
        if((*childIt)->getId() == id) {
            foreach(GobjectCallback callback, (*childIt)->m_onDestroyCallbacks) {
                callback((*childIt).get());
            }
            (*childIt)->m_onDestroyCallbacks.clear();


            childIt->reset();
            m_children.erase(childIt);
            break;
        }

        childIt++;
    }
}

void gx::GObject::removeAllChildren()
{
    m_children.erase(m_children.begin(), m_children.end());
}

gx::Canvas *gx::GObject::getCanvas() const
{
    return m_canvas;
}

void gx::GObject::setCanvas(Canvas *value)
{
    m_canvas = value;
}

void gx::GObject::preparePropertyChange()
{
    preChange();
}

void gx::GObject::updateProperties()
{
    changed();
}

QRectF gx::GObject::boundingBox() const
{
    QRectF box;
    foreach(std::shared_ptr<GObject> obj, m_children)
    {
        box = box.united(obj->boundingBox());
    }

    return box;
}

void gx::GObject::changed()
{
    foreach(GobjectCallback callback, m_onChangeCallbacks) {
        callback(this);
    }
}

void gx::GObject::preChange()
{
    foreach(GobjectCallback callback, m_onPreChangeCallbacks) {
        callback(this);
    }
}

unsigned int gx::GObject::getId() const
{
    return m_id;
}

void gx::GObject::setId(unsigned int id)
{
    m_id = id;
}
