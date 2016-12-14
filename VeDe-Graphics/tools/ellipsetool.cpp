#include "ellipsetool.h"
#include "commands/addgobjectcommand.h"
#include "properties/propertyfactory.h"
#include <QtMath>

gx::EllipseTool::EllipseTool(gx::Canvas *canvas)
    :RestrictableTool(canvas)
{
    setName("Ellipse tool");
    PropertyFactory::addShapeProperties(this);
    QString start = "Place the center";
    QString placeCenter = "Placing center";
    QString wait = "Place second corner";
    QString moveRadiiState = "Move second corner";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(placeCenter, STATE_DEF {
        m_ellipse = std::make_shared<Ellipse>();
        m_ellipse->setCenter(getCanvas()->getCursor());
        m_ellipse->setRadius(Vertex(0,0));
        m_ellipse->copyPropertiesFrom(*this);

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
        m_ellipse.reset();
        setRestricted(false);
        moveToStateSilent(start);
    });


    addTransition(start, Transition(QEvent::MouseButtonPress, Qt::LeftButton), placeCenter);
    addTransition(wait, Transition(QEvent::MouseMove), moveRadiiState);
    addTransition(wait, Transition(QEvent::MouseButtonPress, Qt::LeftButton), finished);

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

    m_ellipse->setRadius(Vertex(rx, ry));
    getCanvas()->redraw();
}
