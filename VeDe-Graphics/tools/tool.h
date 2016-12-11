#ifndef TOOL_H
#define TOOL_H

#include <QMap>
#include <QString>
#include <QVector>
#include <QEvent>
#include <functional>
#include "canvas.h"
#include "transition.h"
#include "properties/propertyholder.h"

namespace gx
{
class Tool : public PropertyHolder
{
    #define EMPTY_STATE [](const Transition&){}
    #define STATE_DEF [=](const Transition& t)
    #define STATE_DEF_NO_CAP (const Transition& t)


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
    Canvas* getCanvas();
    const QString& getCurrStateName() const;
    QVector<QString> getAllStateNames() const;
    void moveToStateSilent(const QString &stateName);

    bool isActive() const;
    void setActive(bool active);
    void switchTo();

    QString getName() const;
    void setName(const QString &name);

protected:
    void addState(const QString &name, ToolStateCallBack callBack);
    void addTransition(const QString &transitionFrom, Transition transition, const QString &transitionTo);

private:
    QMap<QString, ToolState> m_states;
    QString m_currState;
    QString m_name;
    Canvas* m_canvas;
    bool m_active;
};
}

#endif // TOOL_H
