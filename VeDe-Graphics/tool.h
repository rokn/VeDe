#ifndef TOOL_H
#define TOOL_H

#include <QMap>
#include <QString>
#include <QVector>
#include <QEvent>
#include <functional>
#include "canvas.h"

namespace gx
{
class Tool
{
protected:
    typedef std::function<int(QEvent&)> ToolStateCallBack;
    typedef unsigned int uint;

    //Struct/class declarations
private:
    typedef struct
    {
        ToolStateCallBack callback;
        QString name;
    }ToolState;

public:
    Tool(Canvas* canvas);
    void handleEvent(QEvent& event);
    Canvas* getCanvas();
    const QString& getCurrStateName() const;
    QVector<QString> getAllStateNames() const;

protected:

    uint addState(QString name, ToolStateCallBack callBack);
    void addTransition(uint transitionFrom, QEvent::Type event, uint transitionTo);

private:
    QMap<uint, QMap<QEvent::Type, uint>> m_transitions;
    QVector<ToolState> m_states;
    uint m_currState;
    Canvas* m_canvas;


};
}

#endif // TOOL_H
