#include "canvasimpl.h"
#include "converters.h"
//#include "canvaswidget.h"
#include "qtcustompainter.h"
#include "tools/transitiontype.h"
#include <QGraphicsScene>
#include <QGraphicsSceneMouseEvent>
#include <QKeyEvent>
#include <QGuiApplication>


#include "objects/ellipsegraphicsitem.h"
#include "objects/rectgraphicsitem.h"
#include "objects/linegraphicsitem.h"
#include "objects/pathgraphicsitem.h"
#include "objects/ellipse.h"
#include "objects/line.h"
#include "objects/rectangle.h"
#include "objects/path.h"
#include "tools/tool.h"

CanvasImpl::CanvasImpl(QObject *parent, std::shared_ptr<gx::GObject> root)
    :QGraphicsScene(parent), gx::Canvas(root, nullptr)
{
    QColor white = QColor(255,255,255,255);
    addRect(0,0,800,600,QPen(white), QBrush(white));
//    addEllipse(100,100,600,400);
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
    invalidate(0,0,800,600,ForegroundLayer);
}

gx::Vertex CanvasImpl::getCursor() const
{
    return m_mousePos;
}

void CanvasImpl::onAddObject(std::shared_ptr<gx::GObject> object)
{
    //Factory
    if(std::dynamic_pointer_cast<gx::Ellipse>(object) != nullptr) {
        addItem(new EllipseGraphicsItem(std::dynamic_pointer_cast<gx::Ellipse>(object)));
    }
    else if(std::dynamic_pointer_cast<gx::Rectangle>(object) != nullptr) {
        addItem(new RectGraphicsItem(std::dynamic_pointer_cast<gx::Rectangle>(object)));
    }
    else if(std::dynamic_pointer_cast<gx::Line>(object) != nullptr) {
        addItem(new LineGraphicsItem(std::dynamic_pointer_cast<gx::Line>(object)));
    }
    else if(std::dynamic_pointer_cast<gx::Path>(object) != nullptr) {
        addItem(new PathGraphicsItem(std::dynamic_pointer_cast<gx::Path>(object)));
    }
}

void CanvasImpl::drawForeground(QPainter *painter, const QRectF &rect)
{
    if(getCurrTool() != nullptr)
    {
        QtCustomPainter customPainter(painter);
        getCurrTool()->drawGui(&customPainter);
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

CanvasImpl *CanvasImpl::createCanvas(QObject *parent, std::shared_ptr<gx::GObject> root)
{
    CanvasImpl* canvas = new CanvasImpl(parent, root);

    canvas->initModifierKeys();
//    canvas->setFlag(QGraphicsItem::ItemIsFocusable);
//    canvas->setFlag(QGraphicsItem::ItemIsSelectable);
//    canvas->setFocus(Qt::OtherFocusReason);

    return canvas;
}

void CanvasImpl::mouseMoveEvent(QGraphicsSceneMouseEvent *event)
{
//    grabMouse();
    m_mousePos.setX(event->scenePos().x());
    m_mousePos.setY(event->scenePos().y());
    gx::Transition transition(gx::MOUSE_MOVE, event->button());
    handleTransition(transition);
    event->accept();
}

void CanvasImpl::mousePressEvent(QGraphicsSceneMouseEvent *event)
{
//    setFocus(Qt::OtherFocusReason);
    m_mousePos.setX(event->scenePos().x());
    m_mousePos.setY(event->scenePos().y());
    gx::Transition transition(gx::MOUSE_PRESS, event->button());
    handleTransition(transition);
    event->accept();
}

void CanvasImpl::mouseReleaseEvent(QGraphicsSceneMouseEvent *event)
{
    m_mousePos.setX(event->scenePos().x());
    m_mousePos.setY(event->scenePos().y());
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

