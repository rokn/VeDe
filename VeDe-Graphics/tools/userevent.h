#ifndef USEREVENT_H
#define USEREVENT_H

#include <Qt>
#include "usereventtype.h"

namespace gx
{
class UserEvent
{
public:
    UserEvent(UserEventType eventType);
    UserEvent(UserEventType eventType, Qt::Key key);
    UserEvent(UserEventType eventType, Qt::MouseButton button);

    UserEventType eventType() const;
    Qt::Key key() const;
    Qt::MouseButton mouseButton() const;

    bool operator ==(const UserEvent& other) const;
    bool operator !=(const UserEvent& other) const;
    bool operator <(const UserEvent& other) const; // For maps


private:
    UserEventType m_eventType;
    Qt::Key m_key;
    Qt::MouseButton m_mouseButton;

};
}

#endif // USEREVENT_H
