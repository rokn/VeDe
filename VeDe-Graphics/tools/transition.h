#ifndef TRANSITION_H
#define TRANSITION_H

#include <Qt>
#include <QEvent>

namespace gx
{
class Transition
{
public:
    Transition(QEvent::Type eventType);
    Transition(QEvent::Type eventType, Qt::Key key);
    Transition(QEvent::Type eventType, Qt::MouseButton button);

    QEvent::Type eventType() const;
    Qt::Key key() const;
    Qt::MouseButton mouseButton() const;

    bool operator ==(const Transition& other) const;
    bool operator !=(const Transition& other) const;
    bool operator <(const Transition& other) const; // For maps


private:
    QEvent::Type m_eventType;
    Qt::Key m_key;
    Qt::MouseButton m_mouseButton;

};
}

#endif // TRANSITION_H
