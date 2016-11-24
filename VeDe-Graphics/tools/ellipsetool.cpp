#include "ellipsetool.h"
#include "commands/addgobjectcommand.h"
#include <QtMath>

gx::EllipseTool::EllipseTool(gx::Canvas *canvas)
    :Tool(canvas)
{
    uint start = addState("Place the center", EMPTY_STATE);

    uint placeCenter = addState("Placing center", [this](QEvent const&e)->int{
        m_ellipse = std::make_shared<Ellipse>();
        m_ellipse->setCenter(getCanvas()->getCursor());
        m_ellipse->setRadius(Vertex(0,0));

        gx::Command* command = new gx::AddGObjectCommand(m_ellipse, getCanvas());
        getCanvas()->executeCommand(command);
        return 2;
    });

    uint wait = addState("Choose the radii", EMPTY_STATE);

    uint moveRadii = addState("Moving radii", [this](QEvent const&e)->int{
        if(m_ellipse == nullptr){ return 0; }

        Vertex cursorPos = getCanvas()->getCursor();
        float rx = qAbs(cursorPos.x() - m_ellipse->center().x());
        float ry = qAbs(cursorPos.y() - m_ellipse->center().y());

        m_ellipse->setRadius(Vertex(rx, ry));
        getCanvas()->redraw();
        return 2;
    });

    uint finish = addState("Finish", [this](QEvent const&e)->int{
         return 0;
    });

    addTransition(start, QEvent::MouseButtonPress, placeCenter);
    addTransition(wait, QEvent::MouseMove, moveRadii);
    addTransition(wait, QEvent::MouseButtonPress, finish);
}
