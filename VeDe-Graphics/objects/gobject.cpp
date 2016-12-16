#include "gobject.h"
#include "graphics_exceptions.h"
#include <QStack>
#include <QDebug>

gx::GObject::GObject(std::shared_ptr<gx::GObject> parent)
{
    if(parent != nullptr)
    {
        parent->addChild(this, parent);
    }
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

void gx::GObject::paintAll(gx::CustomPainter& painter) //TODO: find a way to make it const
{
    forAllChildren([&painter](GObject* c){
        c->paintSelf(painter);
        return false;
    });
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

unsigned int gx::GObject::getId() const
{
    return m_id;
}

void gx::GObject::setId(unsigned int id)
{
    m_id = id;
}

//gx::PropertyHolder& gx::GObject::getProperties()
//{
//    return m_properties;
//}
//
//const gx::PropertyHolder &gx::GObject::getProperties() const
//{
//    return m_properties;
//}
