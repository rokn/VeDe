#include "gobject.h"
#include <QStack>

gx::GObject::GObject(std::shared_ptr<gx::GObject> parent)
{
    if(parent != nullptr)
    {
        parent->addChild(this);
    }
}

gx::GObject::~GObject()
{
}

void gx::GObject::addChild(gx::GObject *child)
{
    std::shared_ptr<gx::GObject> ch(child);
    addChild(ch);
}

QList<std::shared_ptr<gx::GObject>>& gx::GObject::getChildren()
{
    return m_children;
}

void gx::GObject::addChild(std::shared_ptr<GObject> child)
{
    child->setParent(std::shared_ptr<GObject>(this));
    this->m_children.append(child);
}

void gx::GObject::paintAll(gx::CustomPainter& painter) const
{
    QStack<const GObject*> paintStack;
    const GObject* curr;
    paintStack.push_back(this);

    while(!paintStack.isEmpty())
    {
        curr = paintStack.back();
        paintStack.pop_back();

        curr->paintSelf(painter);

        auto it = curr->m_children.constEnd();

        while(it != curr->m_children.constBegin())
        {
            it--;
            paintStack.push_back((*it).get());
        }
    }
}

std::shared_ptr<gx::GObject> gx::GObject::getParent() const
{
    return m_parent;
}

void gx::GObject::setParent(const std::shared_ptr<GObject> &parent)
{
    m_parent = parent;
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
