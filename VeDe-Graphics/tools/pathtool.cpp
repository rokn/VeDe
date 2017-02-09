#include "pathtool.h"
#include "properties/propertyfactory.h"
#include "commands/addgobjectcommand.h" // TODO: remove
#include "commands/selectcommand.h" // TODO: remove
#include <QtMath>
#include <QDebug>

gx::PathTool::PathTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Path tool");
    m_startState = "Place a point";
    m_placeFirstState = "Place first point";
    QString finishPoint = "Finish point";
    QString addControlPoint = "Add control point";
    QString moveControlPoint = "Move control point";
    QString finishControlPoint = "Finish control point";
    QString startNewPoint = "Start new";
    QString moveNewPoint = "Move new point";
    QString setNewPoint = "Set new point";
    QString removeNewPoint = "Remove new point";

    addState(finishPoint, STATE_DEF {
        if(m_path != nullptr) {
            moveToState(startNewPoint, t);
        } else {
            moveToStateSilent(m_startState);
        }
    });

    addState(addControlPoint, STATE_DEF {
        if(m_path != nullptr) {
            Vertex point = getCanvas()->getCursor();
            m_path->addControlPoint(point);
            moveToStateSilent(moveControlPoint);
//            if(qAbs(point.x() - m_startPoint.x()) < 3 && qAbs(point.y() - m_startPoint.y()) < 3 ) {
//                m_path->addMove(-1);
//                moveToState(finished, t);
//            } else {
//            }
        } else {
            moveToStateSilent(m_startState);
        }
    });

    addState(moveControlPoint, STATE_DEF {
        if(m_path != nullptr) {
            Vertex point = getCanvas()->getCursor();
            m_path->changeLastControl(point);
        } else {
            moveToStateSilent(m_startState);
        }
    });

    addState(finishControlPoint, STATE_DEF {
        if(m_path != nullptr) {
              moveToState(startNewPoint, t);
        } else {
            moveToStateSilent(m_startState);
        }
    });

    addState(startNewPoint, STATE_DEF {
        if(m_path != nullptr) {
            Vertex point = getCanvas()->getCursor();
            m_path->addPoint(point);
            moveToStateSilent(moveNewPoint);
        } else {
            moveToStateSilent(m_startState);
        }
    });

    addState(moveNewPoint, STATE_DEF {
        if(m_path != nullptr) {
            Vertex point = getCanvas()->getCursor();
            m_path->changeLastPoint(point);
        } else {
            moveToStateSilent(m_startState);
        }
    });

    addState(setNewPoint, STATE_DEF {
        if(m_path != nullptr) {
        } else {
            moveToStateSilent(m_startState);
        }
    });

    addState(removeNewPoint, STATE_DEF {
        if(m_path != nullptr) {
            m_path->removeLastPoint();
            moveToState(m_finishedState, t);
        } else {
            moveToStateSilent(m_startState);
        }
    });

    initStates(false);

    addTransition(m_placeFirstState, UserEvent(MOUSE_RELEASE, Qt::LeftButton), finishPoint);
    addTransition(m_placeFirstState, UserEvent(MOUSE_MOVE), addControlPoint);
    addTransition(moveControlPoint, UserEvent(MOUSE_MOVE), moveControlPoint);
    addTransition(moveControlPoint, UserEvent(MOUSE_RELEASE, Qt::LeftButton), finishControlPoint);
    addTransition(moveControlPoint, UserEvent(MOUSE_PRESS, Qt::RightButton), m_finishedState);
    addTransition(moveNewPoint, UserEvent(MOUSE_PRESS, Qt::LeftButton), setNewPoint);
    addTransition(moveNewPoint, UserEvent(MOUSE_MOVE), moveNewPoint);
    addTransition(moveNewPoint, UserEvent(MOUSE_PRESS, Qt::RightButton), removeNewPoint);
    addTransition(setNewPoint, UserEvent(MOUSE_RELEASE, Qt::LeftButton), finishPoint);
    addTransition(setNewPoint, UserEvent(MOUSE_MOVE), addControlPoint);
}

bool gx::PathTool::startShape(gx::Vertex mousePos)
{
    m_path = std::make_shared<Path>();
    m_startPoint = getCanvas()->getCursor();
    m_path->addPoint(m_startPoint);
    setShape(m_path);
    return false;
}
