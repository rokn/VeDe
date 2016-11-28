#include "ellipsetool.h"
#include "commands/addgobjectcommand.h"
#include <QtMath>

gx::EllipseTool::EllipseTool(gx::Canvas *canvas)
    :Tool(canvas)
{
    QString start = "Place the center";
    QString placeCenter = "Placing center";
    QString wait = "Place second corner";
    QString moveRadiiState = "Move second corner";
    QString finished = "Finished";
    QString restrictState = "Restrict";
    QString unRestrictState = "UnRestrict";

    m_restricted = false;

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

    addState(moveRadiiState, STATE_DEF {
        if(m_ellipse == nullptr) {
            moveToStateSilent(start);
        }

        moveRadii();

        moveToStateSilent(wait);
    });

    addState(finished, STATE_DEF {
        moveToStateSilent(start);
    });

    addState(restrictState, STATE_DEF{
        m_restricted = true;
        moveRadii();
        moveToStateSilent(wait);
    });

    addState(unRestrictState, STATE_DEF{
        m_restricted = false;
        moveRadii();
        moveToStateSilent(wait);
    });

    addTransition(start, Transition(QEvent::MouseButtonPress, Qt::LeftButton), placeCenter);
    addTransition(wait, Transition(QEvent::MouseMove), moveRadiiState);
    addTransition(wait, Transition(QEvent::MouseButtonPress, Qt::LeftButton), finished);
    addTransition(wait, Transition(QEvent::KeyPress, Qt::Key_Shift), restrictState);
    addTransition(wait, Transition(QEvent::KeyRelease, Qt::Key_Shift), unRestrictState);

    moveToStateSilent(start);
}

void gx::EllipseTool::moveRadii()
{
    Vertex cursorPos = getCanvas()->getCursor();
    float rx = qAbs(cursorPos.x() - m_ellipse->center().x());
    float ry = qAbs(cursorPos.y() - m_ellipse->center().y());

    if(m_restricted) {
        rx = qMax(rx, ry);
        ry = rx;
    }

    m_ellipse->setRadius(Vertex(rx, ry));
    getCanvas()->redraw();
}
