#ifndef EVENT_H
#define EVENT_H

#include <QMap>
#include <functional>
#include "common.h"

namespace gx
{
template <class T>
class Event
{
    typedef std::function<void(T)> Callback;
public:

    Event():m_idCounter(0){}
    Event& operator +=(const Callback& callback)
    {
        m_lastAdded = m_idCounter;
        m_callbacks.insert(m_idCounter++, callback);
        return *this;
    }

    uint addListener(const Callback& callback)
    {
        *this += callback;
        return lastAdded();
    }

    void clearCallbacks()
    {
        m_callbacks.clear();
    }

    void operator ()(T arg)
    {
        foreach (Callback cb, m_callbacks.values()) {
            cb(arg);
        }
    }

    Event& operator -=(const uint& handlerId){
        m_callbacks.remove(handlerId);
        return *this;
    }


    uint lastAdded() const{
        return m_lastAdded;
    }

private:
    uint m_idCounter;
    uint m_lastAdded;
    QMap<uint, Callback> m_callbacks;
};
}

#endif // EVENT_H
