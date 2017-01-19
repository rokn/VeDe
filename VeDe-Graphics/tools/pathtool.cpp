#include "pathtool.h"
#include "commands/addgobjectcommand.h" // TODO: remove
#include <QtMath>

gx::PathTool::PathTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Path tool");
    QString start = "Place a point";
    QString startLine = "Start line";
    QString wait = "Place another point";
    QString curveWait = "Place curve point";
    QString addPoint = "Add point";
    QString makeLine = "Make Line";
    QString makeCurve = "Make Curve";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(startLine, STATE_DEF {
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
                m_path->addMove(-1);
                moveToState(finished, t);
            } else {
                m_path->addPoint(point);
            }
        } else {
            moveToStateSilent(start);
        }
    });

    addState(makeLine, STATE_DEF {
        if(m_path != nullptr) {
            m_path->addMove(0);
            getCanvas()->redraw();
            moveToStateSilent(wait);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(curveWait, EMPTY_STATE);

    addState(makeCurve, STATE_DEF {
        if(m_path != nullptr) {
            m_path->addMove(1);
            Vertex point = getCanvas()->getCursor();
            m_path->addPoint(point);
            getCanvas()->redraw();
            moveToStateSilent(wait);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finished, STATE_DEF {
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
    addTransition(addPoint, Transition(MOUSE_MOVE), curveWait);
    addTransition(curveWait, Transition(MOUSE_RELEASE, Qt::LeftButton), makeCurve);
    addTransition(addPoint, Transition(MOUSE_RELEASE, Qt::LeftButton), makeLine);
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
