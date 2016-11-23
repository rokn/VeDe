#ifndef TOOL_H
#define TOOL_H

#include <QMap>
#include <QVector>
#include <QEvent>
#include <functional>
#include "canvas.h"

namespace gx
{
class Tool
{
public:
    Tool(Canvas* canvas);
    void handleEvent(QEvent& event);
    Canvas* getCanvas();

protected:
    typedef std::function<int(QEvent&)> ToolState;
    typedef unsigned int uint;

    uint addState(ToolState state);
    void addTransition(uint transitionFrom, QEvent::Type event, uint transitionTo);
private:
    QMap<uint, QMap<QEvent::Type, uint>> m_transitions;
    QVector<ToolState> m_states;
    uint m_currState;
    Canvas* m_canvas;
};
}

#endif // TOOL_H
