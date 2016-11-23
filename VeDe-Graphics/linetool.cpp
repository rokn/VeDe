#include "linetool.h"

gx::LineTool::LineTool(gx::Canvas *canvas)
    :Tool(canvas)
{
    uint start = addState([](QEvent& e)->int{
        return -1;
    });

    uint startLine = addState([this](QEvent& e)->int{
        m_line = std::make_shared<Line>();
        m_line->setStart(getCanvas()->getCursor());
        return 2;
    });

    uint wait = addState([](QEvent& e)->int{
        return -1;
    });

    uint moveEnd = addState([this](QEvent& e)->int{
        if(m_line != nullptr) {
            m_line->setEnd(getCanvas()->getCursor());
            return 2;
        }
        return 0;
    });

    uint finished = addState([](QEvent& e)->int{
        return -1;
    });

    addTransition(start, QEvent::MouseButtonPress, startLine);
    addTransition(wait, QEvent::MouseMove, moveEnd);
    addTransition(wait, QEvent::MouseButtonPress, finished);
}
