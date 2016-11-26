#include "ellipsetool.h"
#include "commands/addgobjectcommand.h"
#include <QtMath>

gx::EllipseTool::EllipseTool(gx::Canvas *canvas)
    :Tool(canvas)
{
    QString start = "Place the center";
    QString placeCenter = "Placing center";
    QString wait = "Place second corner";
    QString moveRadii = "Move second corner";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(placeCenter, STATE_DEF {
        m_ellipse = std::make_shared<Ellipse>();
        m_ellipse->setCenter(getCanvas()->getCursor());
        m_ellipse->setRadius(Vertex(0,0));

        gx::Command* command = new gx::AddGObjectCommand(m_ellipse, getCanvas());
        getCanvas()->executeCommand(command);
        moveToStateSilent(wait);
    });

    addState(wait, EMPTY_STATE);

    addState(moveRadii, STATE_DEF {
        if(m_ellipse == nullptr) {
            moveToStateSilent(start);
        }

        Vertex cursorPos = getCanvas()->getCursor();
        float rx = qAbs(cursorPos.x() - m_ellipse->center().x());
        float ry = qAbs(cursorPos.y() - m_ellipse->center().y());

        m_ellipse->setRadius(Vertex(rx, ry));
        getCanvas()->redraw();
        moveToStateSilent(wait);
    });

    addState(finished, STATE_DEF {
        moveToStateSilent(start);
    });

    addTransition(start, Transition(QEvent::MouseButtonPress, Qt::LeftButton), placeCenter);
    addTransition(wait, Transition(QEvent::MouseMove), moveRadii);
    addTransition(wait, Transition(QEvent::MouseButtonPress, Qt::LeftButton), finished);

    moveToStateSilent(start);
}
