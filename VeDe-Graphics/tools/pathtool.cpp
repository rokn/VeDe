#include "pathtool.h"
#include "properties/propertyfactory.h"
#include "commands/addgobjectcommand.h" // TODO: remove
#include <QtMath>
#include <QDebug>

gx::PathTool::PathTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Path tool");
    QString start = "Place a point";
    QString addStartPoint = "Add start point";
    QString finishPoint = "Finish start point";
    QString addControlPoint = "Add control point";
    QString moveControlPoint = "Move control point";
    QString finishControlPoint = "Finish control point";
    QString startNewPoint = "Start new";
    QString moveNewPoint = "Move new point";
    QString setNewPoint = "Set new point";
    QString removeNewPoint = "Remove new point";
    QString finish = "Finish";

    addState(start, EMPTY_STATE);

    addState(addStartPoint, STATE_DEF {
        m_path = std::make_shared<Path>();
        m_startPoint = getCanvas()->getCursor();
        m_path->addPoint(m_startPoint);
        PropertyFactory::setShapePreviewProperties(m_path.get());

        Command* command = new AddGObjectCommand(m_path, getCanvas());
        getCanvas()->executeCommand(command);
        getCanvas()->lock();

        m_path->setGuiElement(true);
    });

    addState(finishPoint, STATE_DEF {
        if(m_path != nullptr) {
            moveToState(startNewPoint, t);
        } else {
            moveToStateSilent(start);
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
            moveToStateSilent(start);
        }
    });

    addState(moveControlPoint, STATE_DEF {
        if(m_path != nullptr) {
            Vertex point = getCanvas()->getCursor();
            m_path->changeLastControl(point);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finishControlPoint, STATE_DEF {
        if(m_path != nullptr) {
              moveToState(startNewPoint, t);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(startNewPoint, STATE_DEF {
        if(m_path != nullptr) {
            Vertex point = getCanvas()->getCursor();
            m_path->addPoint(point);
            moveToStateSilent(moveNewPoint);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(moveNewPoint, STATE_DEF {
        if(m_path != nullptr) {
            Vertex point = getCanvas()->getCursor();
            m_path->changeLastPoint(point);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(setNewPoint, STATE_DEF {
        if(m_path != nullptr) {
        } else {
            moveToStateSilent(start);
        }
    });

    addState(removeNewPoint, STATE_DEF {
        if(m_path != nullptr) {
            m_path->removeLastPoint();
            moveToState(finish, t);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finish, STATE_DEF {
        setRestricted(false);
        m_path->setGuiElement(false);
        m_path->copyPropertiesFrom(*this);
        m_path->copyPropertiesFrom(*getCanvas());
        m_path->updateProperties();

        getCanvas()->redraw(m_path->boundingBox());
        getCanvas()->unlock();

        m_path.reset();
        moveToStateSilent(start);
    });

    addTransition(start, Transition(MOUSE_PRESS, Qt::LeftButton), addStartPoint);
    addTransition(addStartPoint, Transition(MOUSE_RELEASE, Qt::LeftButton), finishPoint);
    addTransition(addStartPoint, Transition(MOUSE_MOVE), addControlPoint);
    addTransition(moveControlPoint, Transition(MOUSE_MOVE), moveControlPoint);
    addTransition(moveControlPoint, Transition(MOUSE_RELEASE, Qt::LeftButton), finishControlPoint);
    addTransition(moveControlPoint, Transition(MOUSE_PRESS, Qt::RightButton), finish);
    addTransition(moveNewPoint, Transition(MOUSE_PRESS, Qt::LeftButton), setNewPoint);
    addTransition(moveNewPoint, Transition(MOUSE_MOVE), moveNewPoint);
    addTransition(moveNewPoint, Transition(MOUSE_PRESS, Qt::RightButton), removeNewPoint);
    addTransition(setNewPoint, Transition(MOUSE_RELEASE, Qt::LeftButton), finishPoint);
    addTransition(setNewPoint, Transition(MOUSE_MOVE), addControlPoint);

//    setUpRestriction(, STATE_DEF{
//        moveEndPoint();
//    });

    moveToStateSilent(start);
}
