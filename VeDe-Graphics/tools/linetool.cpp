#include "linetool.h"
#include "commands/addgobjectcommand.h" // TODO: remove
#include <QtMath>

gx::LineTool::LineTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Line tool");
    QString start = "Place a point";
    QString startLine = "Start line";
    QString wait = "Place end point";
    QString moveEnd = "Move end";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(startLine, STATE_DEF {
        m_line = std::make_shared<Line>();
        m_line->copyPropertiesFrom(*this);
        m_line->copyPropertiesFrom(*getCanvas());
        m_line->setStart(getCanvas()->getCursor());
        m_line->setEnd(getCanvas()->getCursor());

        Command* command = new AddGObjectCommand(m_line, getCanvas());
        getCanvas()->executeCommand(command);
        moveToStateSilent(wait);
    });

    addState(wait, EMPTY_STATE);

    addState(moveEnd, STATE_DEF {
        if(m_line != nullptr) {
            moveEndPoint();
            moveToStateSilent(wait);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finished, STATE_DEF {
        setRestricted(false);
        m_line.reset();
        moveToStateSilent(start);
    });

    addTransition(start, Transition(QEvent::MouseButtonPress,Qt::LeftButton), startLine);
    addTransition(wait, Transition(QEvent::MouseMove), moveEnd);
    addTransition(wait, Transition(QEvent::MouseButtonPress, Qt::LeftButton), finished);

    setUpRestriction(wait, STATE_DEF{
        moveEndPoint();
    });

    moveToStateSilent(start);
}

void gx::LineTool::restrictPos(const gx::Vertex& p1, gx::Vertex &p2)
{
    unsigned int x_diff = qAbs(p2.x() - p1.x());
    unsigned int y_diff = qAbs(p2.y() - p1.y());
    unsigned int max_diff = qMax(x_diff, y_diff);
    int diff = x_diff - y_diff;

    if(qAbs(diff) > max_diff / 2)
    {
        if(diff > 0)
        {
            p2.setY(p1.y());
        }
        else
        {
            p2.setX(p1.x());
        }
    }
    else
    {
        if(p2.x() < p1.x() && p2.y() < p1.y()) {
            p2.setX(p1.x() - max_diff);
            p2.setY(p1.y() - max_diff);
        }
        else if(p2.x() > p1.x() && p2.y() < p1.y()) {
            p2.setX(p1.x() + max_diff);
            p2.setY(p1.y() - max_diff);
        }
        else if(p2.x() < p1.x() && p2.y() > p1.y()) {
            p2.setX(p1.x() - max_diff);
            p2.setY(p1.y() + max_diff);
        }
        else if(p2.x() > p1.x() && p2.y() > p1.y()) {
            p2.setX(p1.x() + max_diff);
            p2.setY(p1.y() + max_diff);
        }
    }
}

void gx::LineTool::moveEndPoint()
{
    Vertex pos = getCanvas()->getCursor();

    if(isRestricted())
    {
        restrictPos(m_line->start(), pos);
    }

    m_line->setEnd(pos);
    getCanvas()->redraw();
}
