#include "pathtool.h"
#include "commands/addgobjectcommand.h" // TODO: remove
#include <QtMath>
#include <QDebug>

gx::PathTool::PathTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Path tool");
    QString start = "Place a point";
<<<<<<< HEAD
    QString startLine = "Start line";
    QString wait = "Place another point";
    QString startCurve = "Start curve";
    QString curveMove = "Place curve point";
    QString addPoint = "Add point";
    QString makeLine = "Make Line";
    QString finishCurve = "Make Curve";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(startLine, STATE_DEF {
        qInfo() << "Started a line";
=======
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
        //qInfo() << addStartPoint;
>>>>>>> rework/canvas
        m_path = std::make_shared<Path>();
        m_path->setCanvas(getCanvas());
        m_path->setGuiElement(true);
        m_startPoint = getCanvas()->getCursor();
        m_path->addPoint(m_startPoint);

        Command* command = new AddGObjectCommand(m_path, getCanvas());
        getCanvas()->executeCommand(command);
    });

    addState(finishPoint, STATE_DEF {
        if(m_path != nullptr) {
            //qInfo() << finishPoint;
            moveToState(startNewPoint, t);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(addControlPoint, STATE_DEF {
        if(m_path != nullptr) {
            //qInfo() << addControlPoint;
            Vertex point = getCanvas()->getCursor();
<<<<<<< HEAD
            if(qAbs(point.x() - m_startPoint.x()) < 3 && qAbs(point.y() - m_startPoint.y()) < 3 ) {
                qInfo() << "Closed path";
                m_path->addMove(-1);
                moveToState(finished, t);
            } else {
                qInfo() << "Added a point";
                m_path->addPoint(point);
                m_path->addMove(0);
                getCanvas()->redraw();
//                moveToState(makeLine, t);
            }
=======
            m_path->addControlPoint(point);
            moveToStateSilent(moveControlPoint);
//            if(qAbs(point.x() - m_startPoint.x()) < 3 && qAbs(point.y() - m_startPoint.y()) < 3 ) {
//                m_path->addMove(-1);
//                moveToState(finished, t);
//            } else {
//            }
>>>>>>> rework/canvas
        } else {
            moveToStateSilent(start);
        }
    });

    addState(moveControlPoint, STATE_DEF {
        if(m_path != nullptr) {
<<<<<<< HEAD
            qInfo() << "Made line";
            getCanvas()->redraw();
            moveToStateSilent(wait);
=======
            //qInfo() << moveControlPoint;
            Vertex point = getCanvas()->getCursor();
            m_path->changeLastControl(point);
//            getCanvas()->redraw();
>>>>>>> rework/canvas
        } else {
            moveToStateSilent(start);
        }
    });

<<<<<<< HEAD
    addState(startCurve, STATE_DEF{
        if(m_path != nullptr) {
            qInfo() << "started curve";
            Vertex point = getCanvas()->getCursor();
            m_path->addPoint(point);
            m_path->changeLastMove(1);
            getCanvas()->redraw();
            moveToState(curveMove, t);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(curveMove, STATE_DEF{
        if(m_path != nullptr) {
            qInfo() << "Moved curve control";
            Vertex point = getCanvas()->getCursor();
            m_path->changeLastPoint(point);
            getCanvas()->redraw();
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finishCurve, STATE_DEF {
        if(m_path != nullptr) {
            qInfo() << "FinishedCurve";
            getCanvas()->redraw();
            moveToStateSilent(wait);
=======
    addState(finishControlPoint, STATE_DEF {
        if(m_path != nullptr) {
                //qInfo() << moveControlPoint;
              moveToState(startNewPoint, t);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(startNewPoint, STATE_DEF {
        if(m_path != nullptr) {
            //qInfo() << startNewPoint;
            Vertex point = getCanvas()->getCursor();
            m_path->addPoint(point);
//            getCanvas()->redraw();
            moveToStateSilent(moveNewPoint);
>>>>>>> rework/canvas
        } else {
            moveToStateSilent(start);
        }
    });

<<<<<<< HEAD
    addState(finished, STATE_DEF {
        qInfo() << "Finished Path";
=======
    addState(moveNewPoint, STATE_DEF {
        if(m_path != nullptr) {
            //qInfo() << moveNewPoint;
            Vertex point = getCanvas()->getCursor();
            m_path->changeLastPoint(point);
//            getCanvas()->redraw();
        } else {
            moveToStateSilent(start);
        }
    });

    addState(setNewPoint, STATE_DEF {
        if(m_path != nullptr) {
            //qInfo() << setNewPoint;
//              moveToState(startNewPoint, t);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(removeNewPoint, STATE_DEF {
        if(m_path != nullptr) {
            //qInfo() << removeNewPoint;
            m_path->removeLastPoint();
            moveToState(finish, t);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finish, STATE_DEF {
        //qInfo() << finish;
>>>>>>> rework/canvas
        setRestricted(false);
        m_path->setGuiElement(false);
        m_path->copyPropertiesFrom(*this);
        m_path->copyPropertiesFrom(*getCanvas());
        m_path->updateProperties();
//        getCanvas()->redraw();
        m_path.reset();
        moveToStateSilent(start);
    });

<<<<<<< HEAD
    addTransition(start, Transition(MOUSE_PRESS, Qt::LeftButton), startLine);
    addTransition(startLine, Transition(MOUSE_RELEASE, Qt::LeftButton), wait);
//    addTransition(wait, Transition(MOUSE_MOVE), moveEnd);
    addTransition(wait, Transition(MOUSE_PRESS, Qt::LeftButton), addPoint);
    addTransition(addPoint, Transition(MOUSE_RELEASE, Qt::LeftButton), makeLine);
    addTransition(addPoint, Transition(MOUSE_MOVE), startCurve);
    addTransition(curveMove, Transition(MOUSE_MOVE), curveMove);
    addTransition(curveMove, Transition(MOUSE_RELEASE, Qt::LeftButton), finishCurve);
    addTransition(wait, Transition(MOUSE_PRESS, Qt::RightButton), finished);
=======
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
>>>>>>> rework/canvas

//    setUpRestriction(, STATE_DEF{
//        moveEndPoint();
//    });

    moveToStateSilent(start);
}

//void gx::LineTool::restrictPos(const gx::Vertex& p1, gx::Vertex &p2)
//{
//    unsigned int x_diff = qAbs(p2.x() - p1.x());
//    unsigned int y_diff = qAbs(p2.y() - p1.y());
//    unsigned int max_diff = qMax(x_diff, y_diff);
//    int diff = x_diff - y_diff;

//    if(qAbs(diff) > max_diff / 2)
//    {
//        if(diff > 0)
//        {
//            p2.setY(p1.y());
//        }
//        else
//        {
//            p2.setX(p1.x());
//        }
//    }
//    else
//    {
//        if(p2.x() < p1.x() && p2.y() < p1.y()) {
//            p2.setX(p1.x() - max_diff);
//            p2.setY(p1.y() - max_diff);
//        }
//        else if(p2.x() > p1.x() && p2.y() < p1.y()) {
//            p2.setX(p1.x() + max_diff);
//            p2.setY(p1.y() - max_diff);
//        }
//        else if(p2.x() < p1.x() && p2.y() > p1.y()) {
//            p2.setX(p1.x() - max_diff);
//            p2.setY(p1.y() + max_diff);
//        }
//        else if(p2.x() > p1.x() && p2.y() > p1.y()) {
//            p2.setX(p1.x() + max_diff);
//            p2.setY(p1.y() + max_diff);
//        }
//    }
//}
