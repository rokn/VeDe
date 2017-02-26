#include "gobject.h"
#include "helpers.h"
#include "canvas.h"
#include "graphics_exceptions.h"
#include <QStack>
#include <QDebug>

gx::GObject::GObject(gx::SharedGObject parent)
{
    if(parent != nullptr)
    {
        parent->addChild(this);
    }
    m_canvas = nullptr;
    m_selected = false;

    onChange() += [this](const GObject *o){
        clearControlPoints();
        updateControlPoints();
    };
    updateControlPoints();
}

gx::GObject::~GObject()
{
}

void gx::GObject::addChild(gx::GObject *child)
{
    gx::SharedGObject ch(child);
    addChild(ch);
}

QList<gx::SharedGObject>& gx::GObject::getChildren()
{
    return m_children;
}

void gx::GObject::addChild(SharedGObject child)
{
    child->setParent(this);
    this->m_children.append(child);
}

gx::GObject *gx::GObject::getParent() const
{
    return m_parent;
}

void gx::GObject::setParent(GObject *parent)
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

gx::Event<const gx::GObject *> &gx::GObject::onDestroy()
{
    return m_onDestroy;
}

gx::Event<const gx::GObject*> &gx::GObject::onPreChange()
{
    return m_onPreChange;
}

gx::Event<const gx::GObject *> &gx::GObject::onChange()
{
    return m_onChange;
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
            (*childIt)->m_onDestroy((*childIt).get());
            (*childIt)->clearAllEvents();
            if((*childIt)->isSelected()){
                getCanvas()->deselectObject(*childIt);
            }

            childIt->reset();
            m_children.erase(childIt);
            break;
        }

        childIt++;
    }
}

void gx::GObject::removeAllChildren()
{
    m_children.erase(m_children.begin(), m_children.end()); // TODO: Connect to removeChild function
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
    foreach(SharedGObject obj, m_children)
    {
        box = box.united(obj->boundingBox());
    }

    return box.united(shapeBoundingBox());
}

bool gx::GObject::containsPoint(const gx::Vertex &point) const
{
    if(shapeContainsPoint(point)) return true;

    foreach(SharedGObject obj, m_children)
    {
        if(obj->containsPoint(point)) {
            return true;
        }
    }

    return false;
}

void gx::GObject::changed()
{
    m_onChange(this);
}

void gx::GObject::preChange()
{
    m_onPreChange(this);
}

QRectF gx::GObject::shapeBoundingBox() const
{
    return QRectF();
}

bool gx::GObject::shapeContainsPoint(const gx::Vertex &point) const
{
    return false;
}

void gx::GObject::updateControlPoints()
{
}

void gx::GObject::addControlPoint(gx::ControlPoint *point)
{
    m_controlPoints.append(point);
}

void gx::GObject::clearControlPoints()
{
    foreach(auto point, m_controlPoints) {
        delete point;
    }

    m_controlPoints.clear();
}

void gx::GObject::applyTranslation()
{
    m_transform = m_transform * m_translation ;
}

void gx::GObject::removeTranslation()
{
    m_transform = m_transform * m_translation.inverted();
}

QTransform gx::GObject::getCenterAxis() const
{
    QPointF center = boundingBox().center();
    return QTransform::fromTranslate(center.x(), center.y());
}

void gx::GObject::translate(gx::Vertex translation)
{
    preChange();
    removeTranslation();
    m_translation.translate(translation.x(), translation.y());
    applyTranslation();
    changed();
}

void gx::GObject::scale(gx::Vertex scaleBy)
{
    scale(scaleBy, getCenterAxis());
}

void gx::GObject::scale(gx::Vertex scaleBy, QTransform axis)
{
    preChange();
    QTransform scaleMatrix = QTransform::fromScale(scaleBy.x(), scaleBy.y());
    m_transform = m_transform * axis.inverted() * scaleMatrix * axis;
    changed();
}

void gx::GObject::rotate(double angle)
{
    rotate(angle, getCenterAxis());
}

void gx::GObject::rotate(double angle, QTransform axis)
{
    preChange();
    QTransform rotation;
    rotation.rotate(angle);
    m_transform = m_transform * axis.inverted() * rotation * axis;
    changed();
}

void gx::GObject::clearAllEvents()
{
    m_onDestroy.clearCallbacks();
    m_onPreChange.clearCallbacks();
    m_onChange.clearCallbacks();
}

QList<gx::ControlPoint *> gx::GObject::getControlPoints()
{
    QList<ControlPoint*> allPoints;

    foreach(SharedGObject obj, m_children)
    {
        allPoints.append(getControlPoints());
    }

    allPoints.append(m_controlPoints);
    return allPoints;
}

const QTransform& gx::GObject::getTransform() const
{
    return m_transform;
}

bool gx::GObject::isSelected() const
{
    return m_selected;
}

void gx::GObject::setSelected(bool selected)
{
    m_selected = selected;
}

unsigned int gx::GObject::getId() const
{
    return m_id;
}

void gx::GObject::setId(unsigned int id)
{
    m_id = id;
}
