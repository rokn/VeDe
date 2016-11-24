#include "tool.h"

gx::Tool::Tool(gx::Canvas *canvas)
    :m_canvas(canvas)
{
    m_currState = 0;
}

void gx::Tool::handleEvent(QEvent &event)
{
    auto transitions = m_transitions.value(m_currState);

    if(transitions.contains(event.type()))
    {
        m_currState = transitions.value(event.type());
        int switchState = m_states.at(m_currState).callback(event);

        if(switchState >= 0)
        {
            m_currState = switchState;
        }
    }
}

gx::Canvas *gx::Tool::getCanvas()
{
    return m_canvas;
}

const QString &gx::Tool::getCurrStateName() const
{
    return m_states.value(m_currState).name;
}

QVector<QString> gx::Tool::getAllStateNames() const
{
    QVector<QString> stateNames;

    for(auto& state : m_states)
    {
        stateNames.append(state.name);
    }

    return stateNames;
}

uint gx::Tool::addState(QString name, ToolStateCallBack callBack)
{
    uint id = m_states.size();
    ToolState state;
    state.name = name;
    state.callback = callBack;

    m_states.append(state);

    QMap<QEvent::Type, uint> map;
    m_transitions.insert(id, map);

    return id;
}

void gx::Tool::addTransition(uint transitionFrom, QEvent::Type event, uint transitionTo)
{
    auto itMap = m_transitions.find(transitionFrom);

    if(itMap != m_transitions.end())
    {
        itMap->insert(event, transitionTo);
    }
}
