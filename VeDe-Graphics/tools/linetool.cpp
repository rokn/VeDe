#include "linetool.h"
#include "properties/propertyfactory.h"
#include "commands/addgobjectcommand.h" // TODO: remove
#include <QtMath>

gx::LineTool::LineTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Line tool");
    QString start = "Place a point";
    QString startLine = "Start line";
    QString moveEnd = "Place end point";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(startLine, STATE_DEF {
        m_line = std::make_shared<Line>();
        PropertyFactory::setShapePreviewProperties(m_line.get());
        Vertex startPos = getCanvas()->getCursor();
        m_line->setStart(startPos);
        startPos.setX(startPos.x()+0.0001f);//Disable buggy division by zero
        m_line->setEnd(startPos);
        Command* command = new AddGObjectCommand(m_line, getCanvas());
        getCanvas()->executeCommand(command);
        getCanvas()->lock();

        m_line->setGuiElement(true);

        moveToStateSilent(moveEnd);
    });

    addState(moveEnd, STATE_DEF {
        if(m_line != nullptr) {
            moveEndPoint();
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finished, STATE_DEF {
        setRestricted(false);
        m_line->setGuiElement(false);
        m_line->copyPropertiesFrom(*this);
        m_line->copyPropertiesFrom(*getCanvas());
        m_line->updateProperties();
        getCanvas()->redraw(m_line->boundingBox());
        getCanvas()->unlock();
        m_line.reset();
        moveToStateSilent(start);
    });

    addTransition(start, Transition(MOUSE_PRESS, Qt::LeftButton), startLine);
    addTransition(moveEnd, Transition(MOUSE_MOVE), moveEnd);
    addTransition(moveEnd, Transition(MOUSE_RELEASE, Qt::LeftButton), finished);

    setUpRestriction(STATE_DEF{
        if(m_line != nullptr){
            moveEndPoint();
        }
    });

    moveToStateSilent(start);
}

void gx::LineTool::drawGui(gx::CustomPainter *painter) const
{
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
}
