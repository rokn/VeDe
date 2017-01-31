#include "tool.h"
#include <QDebug>

gx::Tool::Tool(gx::Canvas *canvas)
    :m_canvas(canvas)
{
}

void gx::Tool::handleEvent(const Transition& transition)
{
    auto state = m_states.find(m_currState);
    if(state == m_states.end()) return;

    auto transitions = state->transitions;

    if(transitions.contains(transition))
    {
        m_currState = transitions.value(transition);
        m_states.find(m_currState)->callback(transition);
    }
}

gx::Canvas *gx::Tool::getCanvas()
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

void gx::Tool::moveToState(const QString &stateName, Transition transition) {
    m_currState = stateName;
    m_states.find(m_currState)->callback(transition);
}

void gx::Tool::moveToStateSilent(const QString &stateName)
{
     //TODO: See if necessary
//    if(m_states.find(stateName) != m_states.end())
//    {
        m_currState = stateName;
//    }
}


void gx::Tool::addState(const QString& name, ToolStateCallBack callBack)
{
    ToolState state;
    state.name = name;
    state.callback = callBack;

    m_states.insert(name, state);
}

void gx::Tool::addTransition(const QString& transitionFrom, Transition transition, const QString& transitionTo)
{
    auto state = m_states.find(transitionFrom);

    if(state != m_states.end())
    {
        state.value().transitions.insert(transition, transitionTo);
    }
}

QString gx::Tool::getName() const
{
    return m_name;
}

void gx::Tool::setName(const QString &name)
{
    m_name = name;
}

void gx::Tool::drawGui(gx::CustomPainter *painter) const
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
