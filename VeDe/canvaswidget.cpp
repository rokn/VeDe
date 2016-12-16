#include "canvaswidget.h"
#include "objects/ellipse.h"
#include "tools/transition.h"
#include "graphics_exceptions.h"
#include "canvasimpl.h"
#include <QMouseEvent>
#include <QGuiApplication>
#include <QPalette>

#include<QAbstractButton>
CanvasWidget::CanvasWidget(QWidget *parent)
    :QWidget(parent), m_canvas(new CanvasImpl(this))
{
    QPalette pal = this->palette();
    pal.setColor(backgroundRole(), Qt::white);
    setPalette(pal);
}

CanvasWidget::CanvasWidget(std::shared_ptr<gx::GObject> root, QWidget *parent)
    :QWidget(parent), m_canvas(new CanvasImpl(this, root))
{
}

void CanvasWidget::initModifierKeys()
{
    m_modifierKeys.insert(Qt::ShiftModifier, false);
    m_modifierKeys.insert(Qt::ControlModifier, false);
    m_modifierKeys.insert(Qt::AltModifier, false);
}

Qt::KeyboardModifier CanvasWidget::transformToMod(Qt::Key key)
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

Qt::Key CanvasWidget::transformToKey(Qt::KeyboardModifier mod)
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

CanvasWidget* CanvasWidget::createCanvasWidget(QWidget *parent, std::shared_ptr<gx::GObject> root)
{
    CanvasWidget* widget = nullptr;

    if(root == nullptr)
    {
        widget = new CanvasWidget(parent);
    }
    else
    {
        widget = new CanvasWidget(root, parent);
    }

    widget->setMouseTracking(true);
    widget->setFocusPolicy(Qt::WheelFocus);
    widget->initModifierKeys();
    widget->m_defaultWidth = widget->width();
    widget->m_defaultHeight = widget->height();
    return widget;
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    if(m_canvas->root() != nullptr)
    {
        QtCustomPainter painter(this);
//        painter.setZoomFactor(m_canvas->getZoomFactor());
        m_canvas->root()->paintAll(painter);
    }
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    gx::Transition transition(event->type(), event->button());
    m_canvas->handleTransition(transition);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    gx::Transition transition(event->type(), event->button());
    m_canvas->handleTransition(transition);
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    gx::Transition transition(event->type(), event->button());
    m_canvas->handleTransition(transition);
}

void CanvasWidget::keyPressEvent(QKeyEvent *event)
{
    Qt::Key key = (Qt::Key)event->key();

    if(m_modifierKeys.contains(transformToMod(key))) {
        m_modifierKeys[transformToMod(key)] = true;
    }

    gx::Transition transition(event->type(), key);
    m_canvas->handleTransition(transition);
}

void CanvasWidget::keyReleaseEvent(QKeyEvent *event)
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

    gx::Transition transition(event->type(), key);
    m_canvas->handleTransition(transition);
}

void CanvasWidget::wheelEvent(QWheelEvent *event)
{
    if(m_modifierKeys[Qt::ControlModifier])
    {
        float zoomFactor = m_canvas->getZoomFactor();
        zoomFactor += event->angleDelta().y() / 300.0f;
        m_canvas->setZoomFactor(zoomFactor);
        update();
    }
//    setFixedWidth(m_defaultWidth * zoomFactor);
//    setFixedHeight(m_defaultHeight * zoomFactor);
}

gx::Canvas *CanvasWidget::getCanvas() const
{
    return m_canvas;
}

void CanvasWidget::setCanvas(gx::Canvas *canvas)
{
    m_canvas = canvas;
}

