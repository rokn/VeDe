#include "tool.h"
#include <QDebug>

gx::Tool::Tool(gx::Canvas *canvas)
    :m_canvas(canvas)
{
}

void gx::Tool::handleEvent(const UserEvent& transition)
{
    auto state = m_states.find(m_currState);
    if(state == m_states.end()) return;
    bool changed = false;
    QString newState;

    auto transitions = state->transitions;

    if(transitions.contains(transition))
    {
        newState = transitions.value(transition);
        changed = true;
    }
    else if(m_globalTransitions.contains(transition))
    {
        newState = m_globalTransitions.value(transition);
        changed = true;
    }

    if(changed)
    {
        m_lastState = m_currState;
        m_currState = newState;
        m_states.find(m_currState)->callback(transition);
    }
}

gx::Canvas *gx::Tool::getCanvas()
{
    return m_canvas;
}

const gx::Canvas *gx::Tool::getCanvas() const
{
    return m_canvas;
}

const QString &gx::Tool::getCurrStateName() const
{
    auto state = m_states.find(m_currState);
    if(state != m_states.end())
    {
        return state.value().name;
    }
    return QString();
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

void gx::Tool::moveToState(const QString &stateName, UserEvent transition) {
    m_currState = stateName;
    m_states.find(m_currState)->callback(transition);
}

void gx::Tool::moveToStateSilent(const QString &stateName)
{
    m_currState = stateName;
}


void gx::Tool::addState(const QString& name, ToolStateCallBack callBack)
{
    ToolState state;
    state.name = name;
    state.callback = callBack;

    m_states.insert(name, state);
}

void gx::Tool::addTransition(const QString& transitionFrom, UserEvent transition, const QString& transitionTo)
{
    if(transitionFrom == ANY_STATE)
    {
        m_globalTransitions.insert(transition, transitionTo);
        return;
    }

    auto state = m_states.find(transitionFrom);

    if(state != m_states.end())
    {
        state.value().transitions.insert(transition, transitionTo);
    }
}

const QString& gx::Tool::getLastState() const
{
    return m_lastState;
}

const QString& gx::Tool::getName() const
{
    return m_name;
}

void gx::Tool::setName(const QString &name)
{
    m_name = name;
}

void gx::Tool::drawGui(gx::CustomPainter &painter) const
{
}

bool gx::Tool::isActive() const
{
    return m_active;
}

void gx::Tool::setActive(bool active)
{
    m_active = active;
}

void gx::Tool::switchTo()
{
    m_canvas->changeCurrTool(this);
}
