#include "canvaswidget.h"
#include "objects/ellipse.h"
#include "tools/transition.h"
#include <QMouseEvent>
#include <QGuiApplication>

CanvasWidget::CanvasWidget(QWidget *parent)
    :QWidget(parent), Canvas()
{
}

CanvasWidget::CanvasWidget(std::unique_ptr<gx::GObject> *root, QWidget *parent)
    :QWidget(parent), Canvas(root)
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
    }
}

CanvasWidget* CanvasWidget::createCanvasWidget(QWidget *parent, std::unique_ptr<gx::GObject> *root)
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
    return widget;
}

void CanvasWidget::paintEvent(QPaintEvent *event)
{
    if(root() != nullptr)
    {
        QtCustomPainter painter(this);
        this->root()->paintAll(painter);
    }
}

void CanvasWidget::redraw()
{
    update();
}

gx::Vertex CanvasWidget::getCursor() const
{
    QPoint relativePos = this->mapFromGlobal(QCursor::pos());
    return gx::Vertex(relativePos.x(), relativePos.y());
}

void CanvasWidget::mouseMoveEvent(QMouseEvent *event)
{
    gx::Transition transition(event->type(), event->button());
    handleEvent(transition);
}

void CanvasWidget::mousePressEvent(QMouseEvent *event)
{
    gx::Transition transition(event->type(), event->button());
    handleEvent(transition);
}

void CanvasWidget::mouseReleaseEvent(QMouseEvent *event)
{
    gx::Transition transition(event->type(), event->button());
    handleEvent(transition);
}

void CanvasWidget::keyPressEvent(QKeyEvent *event)
{
    Qt::Key key = (Qt::Key)event->key();

    if(m_modifierKeys.contains(transformToMod(key))) {
        m_modifierKeys[transformToMod(key)] = true;
    }

    gx::Transition transition(event->type(), key);
    handleEvent(transition);
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
    handleEvent(transition);
}
