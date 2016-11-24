#include "linetool.h"

gx::LineTool::LineTool(gx::Canvas *canvas)
    :Tool(canvas)
{
    uint start = addState("Place a point", [](QEvent& e)->int{
        return -1;
    });

    uint startLine = addState("Start line", [this](QEvent& e)->int{
        m_line = std::make_shared<Line>();
        m_line->setStart(getCanvas()->getCursor());
        return 2;
    });

    uint wait = addState("Place end point", [](QEvent& e)->int{
        return -1;
    });

    uint moveEnd = addState("Move end", [this](QEvent& e)->int{
        if(m_line != nullptr) {
            m_line->setEnd(getCanvas()->getCursor());
            return 2;
        }
        return 0;
    });

    uint finished = addState("Finished", [](QEvent& e)->int{
        return -1;
    });

    addTransition(start, QEvent::MouseButtonPress, startLine);
    addTransition(wait, QEvent::MouseMove, moveEnd);
    addTransition(wait, QEvent::MouseButtonPress, finished);
}

