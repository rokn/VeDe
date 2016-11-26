#include "linetool.h"
#include "commands/addgobjectcommand.h" // TODO: remove

gx::LineTool::LineTool(gx::Canvas *canvas)
    :Tool(canvas)
{
    QString start = "Place a point";
    QString startLine = "Start line";
    QString wait = "Place end point";
    QString moveEnd = "Move end";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(startLine, STATE_DEF {
        m_line = std::make_shared<Line>();
        m_line->setStart(getCanvas()->getCursor());
        m_line->setEnd(getCanvas()->getCursor());

        gx::Command* command = new gx::AddGObjectCommand(m_line, getCanvas());
        getCanvas()->executeCommand(command);
        moveToStateSilent(wait);
    });

    addState(wait, EMPTY_STATE);

    addState(moveEnd, STATE_DEF {
        if(m_line != nullptr) {
            m_line->setEnd(getCanvas()->getCursor());
            getCanvas()->redraw();
            moveToStateSilent(wait);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finished, STATE_DEF {
        moveToStateSilent(start);
    });

    addTransition(start, Transition(QEvent::MouseButtonPress,Qt::LeftButton), startLine);
    addTransition(wait, Transition(QEvent::MouseMove), moveEnd);
    addTransition(wait, Transition(QEvent::MouseButtonPress, Qt::LeftButton), finished);

    moveToStateSilent(start);
}
