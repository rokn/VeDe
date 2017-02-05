#ifndef TOOL_H
#define TOOL_H

#include <QMap>
#include <QString>
#include <QList>
#include <QEvent>
#include <functional>
#include "canvas.h"
#include "custompainter.h"
#include "transition.h"
#include "properties/propertyholder.h"

namespace gx
{
class Tool : public PropertyHolder
{
    #define EMPTY_STATE [](const Transition&){}
    #define STATE_DEF [=](const Transition& t)
    #define STATE_DEF_NO_CAP (const Transition& t)
    #define ANY_STATE "ANY_STATE"


protected:
    typedef std::function<void(const Transition&)> ToolStateCallBack;
//    typedef unsigned int uint;

    //Struct/class declarations
private:
    typedef struct
    {
        ToolStateCallBack callback;
        QString name;
        QMap<Transition, QString> transitions;
    }ToolState;

public:
    Tool(Canvas* canvas);
    void handleEvent(const Transition& transition);
    Canvas *getCanvas();
    const Canvas *getCanvas() const;
    const QString& getCurrStateName() const;
    QVector<QString> getAllStateNames() const;
    void moveToState(const QString &stateName, Transition transition);
    void moveToStateSilent(const QString &stateName);

    bool isActive() const;
    void setActive(bool active);
    void switchTo();

    const QString &getName() const;
    void setName(const QString &name);
    virtual void drawGui(CustomPainter &painter) const;

    const QString& getLastState() const;

protected:
    void addState(const QString &name, ToolStateCallBack callBack);
    void addTransition(const QString &transitionFrom, Transition transition, const QString &transitionTo);

private:
    QMap<QString, ToolState> m_states;
    QMap<Transition, QString> m_globalTransitions;
    QString m_currState;
    QString m_name;
    QString m_lastState;
    Canvas* m_canvas;
    bool m_active;
};
}

#endif // TOOL_H
