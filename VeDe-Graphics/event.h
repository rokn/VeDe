#ifndef EVENT_H
#define EVENT_H

#include <QList>
#include <functional>

namespace gx
{
template <class T>
class Event
{
    typedef std::function<void(T)> Callback;
public:
    Event(){}
    Event& operator +=(const Callback& callback)
    {
        m_callbacks.append(callback);
        return *this;
    }

    void clearCallbacks()
    {
        m_callbacks.clear();
    }

    void operator ()(T arg)
    {
        foreach (Callback cb, m_callbacks) {
            cb(arg);
        }
    }


private:
    QList<Callback> m_callbacks;
};
}

#endif // EVENT_H
