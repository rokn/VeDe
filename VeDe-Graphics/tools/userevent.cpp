#include "userevent.h"

gx::UserEvent::UserEvent(UserEventType eventType)
    :m_eventType(eventType), m_key(Qt::Key_Escape), m_mouseButton(Qt::NoButton)
{
}

gx::UserEvent::UserEvent(UserEventType eventType, Qt::Key key)
    :m_eventType(eventType), m_key(key), m_mouseButton(Qt::NoButton)
{
}

gx::UserEvent::UserEvent(UserEventType eventType, Qt::MouseButton button)
    :m_eventType(eventType), m_key(Qt::Key_Escape), m_mouseButton(button)
{
}

Qt::Key gx::UserEvent::key() const
{
    return m_key;
}

Qt::MouseButton gx::UserEvent::mouseButton() const
{
    return m_mouseButton;
}

bool gx::UserEvent::operator ==(const gx::UserEvent &other) const
{
    bool equal = false;
    equal &= this->m_eventType == other.m_eventType;
    equal &= this->key() == other.key();
    equal &= this->mouseButton() == other.mouseButton();
    return equal;
}

bool gx::UserEvent::operator !=(const gx::UserEvent &other) const
{
    return !(*this == other);
}

bool gx::UserEvent::operator <(const gx::UserEvent &other) const
{
    if(*this != other)
    {
        if(this->eventType() != other.eventType())
        {
            return this->eventType() < other.eventType();
        }
        if(this->key() != other.key())
        {
            return this->key() < other.key();
        }
        if(this->mouseButton() != other.mouseButton())
        {
            return this->mouseButton() < other.mouseButton();
        }
    }

    return false;
}

gx::UserEventType gx::UserEvent::eventType() const
{
    return m_eventType;
}
