#include "canvasimpl.h"
//#include "canvaswidget.h"
#include "qtcustompainter.h"
#include "tools/transitiontype.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGuiApplication>



#include "objects/line.h"

CanvasImpl::CanvasImpl(std::shared_ptr<gx::GObject> root)
    :gx::Canvas(root, nullptr)
{
}

void CanvasImpl::redraw()
{
    this->update();
}

gx::Vertex CanvasImpl::getCursor() const
{
    return m_mousePos;
}

QRectF CanvasImpl::boundingRect() const
{
    return QRectF(x(), y(), x()+800, y() + 600);
}

void CanvasImpl::paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget)
{
    if(root() != nullptr)
    {
        QtCustomPainter customPainter(painter);
        customPainter.setBackColor(gx::Color::fromRgba(255,255,255));
        customPainter.setStrokeColor(gx::Color::fromRgba(255,255,255));
        customPainter.drawRectangle(x(),y(),800,600);
        root()->paintAll(customPainter);
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

CanvasImpl *CanvasImpl::createCanvas(std::shared_ptr<gx::GObject> root)
{
    CanvasImpl* canvas = new CanvasImpl(root);

    canvas->initModifierKeys();
    canvas->setFlag(QGraphicsItem::ItemIsFocusable);
    canvas->setFlag(QGraphicsItem::ItemIsSelectable);
    canvas->setFocus(Qt::OtherFocusReason);

    return canvas;
}

void CanvasImpl::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    grabMouse();
    m_mousePos.setX(event->pos().x());
    m_mousePos.setY(event->pos().y());
    gx::Transition transition(gx::MOUSE_MOVE, event->button());
    handleTransition(transition);
    event->accept();
}

void CanvasImpl::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
    setFocus(Qt::OtherFocusReason);
    m_mousePos.setX(event->pos().x());
    m_mousePos.setY(event->pos().y());
    gx::Transition transition(gx::MOUSE_PRESS, event->button());
    handleTransition(transition);
    event->accept();
}

void CanvasImpl::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mousePos.setX(event->pos().x());
    m_mousePos.setY(event->pos().y());
    gx::Transition transition(gx::MOUSE_RELEASE, event->button());
    handleTransition(transition);
}

void CanvasImpl::keyPressEvent(QKeyEvent *event)
{
    Qt::Key key = (Qt::Key)event->key();

    if(m_modifierKeys.contains(transformToMod(key))) {
        m_modifierKeys[transformToMod(key)] = true;
    }

    gx::Transition transition(gx::KEY_PRESS, key);
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

    gx::Transition transition(gx::KEY_RELEASE, key);
    handleTransition(transition);
}
