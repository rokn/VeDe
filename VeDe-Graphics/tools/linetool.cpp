#include "linetool.h"
#include "commands/addgobjectcommand.h" // TODO: remove

gx::LineTool::LineTool(gx::Canvas *canvas)
    :Tool(canvas)
{
    uint start = addState("Place a point", EMPTY_STATE);

    uint startLine = addState("Start line", [this](QEvent const& e)->int{
        m_line = std::make_shared<Line>();
        m_line->setStart(getCanvas()->getCursor());
        m_line->setEnd(getCanvas()->getCursor());

        gx::Command* command = new gx::AddGObjectCommand(m_line, getCanvas());
        getCanvas()->executeCommand(command);
        return 2;
    });

    uint wait = addState("Place end point", EMPTY_STATE);

    uint moveEnd = addState("Move end", [this](QEvent const& e)->int{
        if(m_line != nullptr) {
            m_line->setEnd(getCanvas()->getCursor());
            getCanvas()->redraw();
            return 2;
        }
        return 0;
    });

    uint finished = addState("Finished", [this](QEvent const& e)->int{
        return 0;
    });

    addTransition(start, QEvent::MouseButtonPress, startLine);
    addTransition(wait, QEvent::MouseMove, moveEnd);
    addTransition(wait, QEvent::MouseButtonPress, finished);
}

