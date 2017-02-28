#include "canvasimpl.h"
#include "converters.h"
#include "qtcustompainter.h"
#include "tools/usereventtype.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGuiApplication>
#include <QApplication>
#include "tools/tool.h"
#include "gobjectmapper.h"

CanvasImpl::CanvasImpl(QObject *parent, double width, double height, gx::SharedGObject root)
    :QGraphicsScene(parent), gx::Canvas(root, width, height)
{
    m_guiDrawer = new GUIDrawer();
    m_guiDrawer->setCanvas(this);

    addItem(m_guiDrawer);
}

CanvasImpl::~CanvasImpl()
{
//    removeItem(m_guiDrawer);
//    delete m_guiDrawer;
}

void CanvasImpl::redraw(QRectF area)
{
    this->update(area);
}

void CanvasImpl::redraw()
{
    this->update(sceneRect());
}

void CanvasImpl::redrawGui()
{
    this->update(sceneRect());
}

gx::Vertex CanvasImpl::getCursor() const
{
    return m_mousePos;
}

bool CanvasImpl::isKeyPressed(Qt::Key key) const
{
    return m_keys.contains(key);
}

void CanvasImpl::onAddObject(gx::SharedGObject object)
{
    QGraphicsItem* item = GObjectMapper::mapToGraphicsItem(object);

    if(item != nullptr) {
        addItem(item);

        object->onDestroy() += [=](const gx::GObject* o)
        {
            this->removeItem(item);
            delete item;
        };
    }
}

void CanvasImpl::initModifierKeys()
{
    m_modifierKeys.insert(Qt::ShiftModifier, false);
    m_modifierKeys.insert(Qt::ControlModifier, false);
    m_modifierKeys.insert(Qt::AltModifier, false);
}

Qt::KeyboardModifier CanvasImpl::transformToMod(Qt::Key key)
{
    switch(key)
    {
        case Qt::Key_Shift:
            return Qt::ShiftModifier;
        case Qt::Key_Control:
            return Qt::ControlModifier;
        case Qt::Key_Alt:
            return Qt::AltModifier;
        default:
            return Qt::NoModifier;
    }
}

Qt::Key CanvasImpl::transformToKey(Qt::KeyboardModifier mod)
{
    switch(mod)
    {
        case Qt::ShiftModifier:
            return Qt::Key_Shift;
        case Qt::ControlModifier:
            return Qt::Key_Control;
        case Qt::AltModifier:
            return Qt::Key_Alt;
        default: throw new UnknownModifierKey;
    }
}

CanvasImpl *CanvasImpl::createCanvas(QObject *parent, double width, double height, gx::SharedGObject root)
{
    CanvasImpl* canvas = new CanvasImpl(parent, width, height, root);

    canvas->initModifierKeys();

    return canvas;
}

void CanvasImpl::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
    m_mousePos.setX(event->scenePos().x());
    m_mousePos.setY(event->scenePos().y());
    gx::UserEvent transition(gx::MOUSE_MOVE, event->button());
    handleTransition(transition);
    event->accept();
}

void CanvasImpl::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    m_mousePos.setX(event->scenePos().x());
    m_mousePos.setY(event->scenePos().y());
    gx::UserEvent transition(gx::MOUSE_PRESS, event->button());
    handleTransition(transition);
    event->accept();
}

void CanvasImpl::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mousePos.setX(event->scenePos().x());
    m_mousePos.setY(event->scenePos().y());
    gx::UserEvent transition(gx::MOUSE_RELEASE, event->button());
    handleTransition(transition);
}

void CanvasImpl::keyPressEvent(QKeyEvent *event)
{
    Qt::Key key = (Qt::Key)event->key();
    m_keys << key;

    if(m_modifierKeys.contains(transformToMod(key))) {
        m_modifierKeys[transformToMod(key)] = true;
    }

    gx::UserEvent transition(gx::KEY_PRESS, key);
    handleTransition(transition);
}

void CanvasImpl::keyReleaseEvent(QKeyEvent *event)
{
    Qt::Key key = (Qt::Key)event->key();

    foreach (auto& mKey, m_modifierKeys.keys()) {
        bool pressed = QGuiApplication::queryKeyboardModifiers().testFlag(mKey);

        if(!pressed && pressed != m_modifierKeys[mKey]) {
            m_modifierKeys[mKey] = pressed;
            key = transformToKey(mKey);
            break;
        }
    }

    m_keys.remove(key);

    gx::UserEvent transition(gx::KEY_RELEASE, key);
    handleTransition(transition);
}

