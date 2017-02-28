#ifndef TOOL_H
#define TOOL_H

#include <QMap>
#include <QString>
#include <QList>
#include <QEvent>
#include <functional>
#include "canvas.h"
#include "custompainter.h"
#include "userevent.h"
#include "properties/propertyholder.h"


#define EMPTY_STATE [](const UserEvent&){}
#define STATE_DEF [=](const UserEvent& t)
#define STATE_DEF_NO_CAP (const UserEvent& t)
#define ANY_STATE "ANY_STATE"

namespace gx
{
class Tool : public PropertyHolder
{
public:
    typedef std::function<void(const UserEvent&)> ToolStateCallBack;

private:
    typedef struct
    {
        ToolStateCallBack callback;
        QString name;
        QMap<UserEvent, QString> transitions;
    }ToolState;

public:

    Tool(Canvas* canvas);
    void handleEvent(const UserEvent& transition);
    Canvas *getCanvas();
    const Canvas *getCanvas() const;
    void setCanvas(Canvas *canvas);
    QString getCurrStateName() const;
    QVector<QString> getAllStateNames() const;
    void moveToState(const QString &stateName, UserEvent transition);
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
    void addTransition(const QString &transitionFrom, UserEvent transition, const QString &transitionTo);

private:
    QMap<QString, ToolState> m_states;
    QMap<UserEvent, QString> m_globalTransitions;
    QString m_currState;
    QString m_name;
    QString m_lastState;
    Canvas* m_canvas;
    bool m_active;
};
}

#endif // TOOL_H
