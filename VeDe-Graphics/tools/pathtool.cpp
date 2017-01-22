#include "pathtool.h"
#include "commands/addgobjectcommand.h" // TODO: remove
#include <QtMath>
#include <QDebug>

gx::PathTool::PathTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Path tool");
    QString start = "Place a point";
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
        m_path = std::make_shared<Path>();
        m_path->setCanvas(getCanvas());
        m_path->setGuiElement(true);
//        m_path->copyPropertiesFrom(*this);
//        m_path->copyPropertiesFrom(*getCanvas());
        m_startPoint = getCanvas()->getCursor();
        m_path->addPoint(m_startPoint);

        Command* command = new AddGObjectCommand(m_path, getCanvas());
        getCanvas()->executeCommand(command);
    });

    addState(wait, EMPTY_STATE);

    addState(addPoint, STATE_DEF {
        if(m_path != nullptr) {
            Vertex point = getCanvas()->getCursor();
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
        } else {
            moveToStateSilent(start);
        }
    });

    addState(makeLine, STATE_DEF {
        if(m_path != nullptr) {
            qInfo() << "Made line";
            getCanvas()->redraw();
            moveToStateSilent(wait);
        } else {
            moveToStateSilent(start);
        }
    });

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
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finished, STATE_DEF {
        qInfo() << "Finished Path";
        setRestricted(false);
        m_path->setGuiElement(false);
        m_path->copyPropertiesFrom(*this);
        m_path->copyPropertiesFrom(*getCanvas());
        getCanvas()->redraw();
        m_path.reset();
        moveToStateSilent(start);
    });

    addTransition(start, Transition(MOUSE_PRESS, Qt::LeftButton), startLine);
    addTransition(startLine, Transition(MOUSE_RELEASE, Qt::LeftButton), wait);
//    addTransition(wait, Transition(MOUSE_MOVE), moveEnd);
    addTransition(wait, Transition(MOUSE_PRESS, Qt::LeftButton), addPoint);
    addTransition(addPoint, Transition(MOUSE_RELEASE, Qt::LeftButton), makeLine);
    addTransition(addPoint, Transition(MOUSE_MOVE), startCurve);
    addTransition(curveMove, Transition(MOUSE_MOVE), curveMove);
    addTransition(curveMove, Transition(MOUSE_RELEASE, Qt::LeftButton), finishCurve);
    addTransition(wait, Transition(MOUSE_PRESS, Qt::RightButton), finished);

    setUpRestriction(wait, STATE_DEF{
//        moveEndPoint();
    });

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
