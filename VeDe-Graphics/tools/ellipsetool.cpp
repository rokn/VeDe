#include "ellipsetool.h"
#include "commands/addgobjectcommand.h"
#include <QtMath>

gx::EllipseTool::EllipseTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Ellipse tool");
    QString start = "Place the center";
    QString placeCenter = "Placing center";
    QString wait = "Place second corner";
    QString moveRadiiState = "Move second corner";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(placeCenter, STATE_DEF {
        m_ellipse = std::make_shared<Ellipse>();
        m_ellipse->copyPropertiesFrom(*this);
        m_ellipse->copyPropertiesFrom(*getCanvas());
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
        setRestricted(false);
        m_ellipse.reset();
        moveToStateSilent(start);
    });


    addTransition(start, Transition(MOUSE_PRESS, Qt::LeftButton), placeCenter);
    addTransition(wait, Transition(MOUSE_MOVE), moveRadiiState);
    addTransition(wait, Transition(MOUSE_PRESS, Qt::LeftButton), finished);

    setUpRestriction(wait, STATE_DEF{
        moveRadii();
    });

    moveToStateSilent(start);
}

void gx::EllipseTool::moveRadii()
{
    Vertex cursorPos = getCanvas()->getCursor();
    float rx = qAbs(cursorPos.x() - m_ellipse->center().x());
    float ry = qAbs(cursorPos.y() - m_ellipse->center().y());

    if(isRestricted()) {
        rx = qMax(rx, ry);
        ry = rx;
    }

    //Disable buggy division by zero
    if(rx < 0.00001){
        rx+=0.00001;
    }
    if(ry < 0.00001) {
        ry += 0.00001;
    }

    m_ellipse->setRadius(Vertex(rx, ry));
    getCanvas()->redraw();
}
