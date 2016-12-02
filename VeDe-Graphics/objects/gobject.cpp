#include "gobject.h"
#include <QStack>

gx::GObject::GObject()
{
}

gx::GObject::~GObject()
{
}

void gx::GObject::addChildren(gx::GObject *child)
{
    std::shared_ptr<gx::GObject> ch(child);
    this->m_children.append(ch);
}

QList<std::shared_ptr<gx::GObject>>& gx::GObject::getChildren()
{
    return m_children;
}

void gx::GObject::addChildren(std::shared_ptr<GObject> child)
{
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

gx::Property *gx::GObject::addProperty(const QString& name, gx::PropertyType propType)
{
    Property* prop = Property::createProperty(name, propType);
    m_properties.insert(name, prop);
    return prop;
}

gx::Property *gx::GObject::getProp(const QString &name) const // TODO add non const method
{
    auto itr = m_properties.find(name);

    if(itr != m_properties.end())
    {
        return itr.value();
    }
    return Q_NULLPTR;
}
