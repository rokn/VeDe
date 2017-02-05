#include "ellipsetool.h"
#include "properties/propertyfactory.h"
#include "commands/addgobjectcommand.h"
#include "commands/selectcommand.h" // TODO: remove
#include <QtMath>

gx::EllipseTool::EllipseTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Ellipse tool");
    QString start = "Place the center";
    QString placeCenter = "Placing center";
    QString moveRadiiState = "Choose radii";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(placeCenter, STATE_DEF {
        m_ellipse = std::make_shared<Ellipse>();
        m_ellipse->setCenter(getCanvas()->getCursor());
        m_ellipse->setRadius(Vertex(0,0));
        PropertyFactory::setShapePreviewProperties(m_ellipse.get());

        gx::Command* command = new gx::AddGObjectCommand(m_ellipse, getCanvas());
        getCanvas()->executeCommand(command);
        getCanvas()->lock();

        m_ellipse->setGuiElement(true);
        moveToStateSilent(moveRadiiState);
    });

    addState(moveRadiiState, STATE_DEF {
        if(m_ellipse == nullptr) {
            moveToStateSilent(start);
        }

        moveRadii();
    });

    addState(finished, STATE_DEF {
        m_ellipse->setGuiElement(false);
        m_ellipse->copyPropertiesFrom(*this);
        m_ellipse->copyPropertiesFrom(*getCanvas());
        m_ellipse->updateProperties();

        getCanvas()->redraw(m_ellipse->boundingBox());
        getCanvas()->unlock();

        getCanvas()->clearSelectedObjects(false);
        getCanvas()->selectObject(m_ellipse);

        m_ellipse.reset();
        moveToStateSilent(start);
    });


    addTransition(start, UserEvent(MOUSE_PRESS, Qt::LeftButton), placeCenter);
    addTransition(moveRadiiState, UserEvent(MOUSE_MOVE), moveRadiiState);
    addTransition(moveRadiiState, UserEvent(MOUSE_RELEASE, Qt::LeftButton), finished);

    setUpRestriction(STATE_DEF{
        if(m_ellipse != nullptr){
            moveRadii();
        }
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
