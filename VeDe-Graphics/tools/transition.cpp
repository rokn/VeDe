#include "transition.h"

gx::Transition::Transition(QEvent::Type eventType)
    :m_eventType(eventType), m_key(Qt::Key_Escape), m_mouseButton(Qt::NoButton)
{
}

gx::Transition::Transition(QEvent::Type eventType, Qt::Key key)
    :m_eventType(eventType), m_key(key), m_mouseButton(Qt::NoButton)
{
}

gx::Transition::Transition(QEvent::Type eventType, Qt::MouseButton button)
    :m_eventType(eventType), m_key(Qt::Key_Escape), m_mouseButton(button)
{
}

Qt::Key gx::Transition::key() const
{
    return m_key;
}

Qt::MouseButton gx::Transition::mouseButton() const
{
    return m_mouseButton;
}

bool gx::Transition::operator ==(const gx::Transition &other) const
{
    bool equal = false;
    equal &= this->m_eventType == other.m_eventType;
    equal &= this->key() == other.key();
    equal &= this->mouseButton() == other.mouseButton();
    return equal;
}

bool gx::Transition::operator !=(const gx::Transition &other) const
{
    return !(*this == other);
}

bool gx::Transition::operator <(const gx::Transition &other) const
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

QEvent::Type gx::Transition::eventType() const
{
    return m_eventType;
}
