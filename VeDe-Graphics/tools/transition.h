#ifndef TRANSITION_H
#define TRANSITION_H

#include <Qt>
#include "transitiontype.h"

namespace gx
{
class Transition
{
public:
    Transition(TransitionType eventType);
    Transition(TransitionType eventType, Qt::Key key);
    Transition(TransitionType eventType, Qt::MouseButton button);

    TransitionType eventType() const;
    Qt::Key key() const;
    Qt::MouseButton mouseButton() const;

    bool operator ==(const Transition& other) const;
    bool operator !=(const Transition& other) const;
    bool operator <(const Transition& other) const; // For maps


private:
    TransitionType m_eventType;
    Qt::Key m_key;
    Qt::MouseButton m_mouseButton;

};
}

#endif // TRANSITION_H
