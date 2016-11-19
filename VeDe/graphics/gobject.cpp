#include "gobject.h"
#include <QStack>

gx::GObject::GObject()
{
}

void gx::GObject::addChildren(std::shared_ptr<GObject> child)
{
    m_children.append(child);
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

        auto it = m_children.constEnd();

        while(it != m_children.constBegin())
        {
            it--;
            paintStack.push_back((*it).get());
        }
    }
}
