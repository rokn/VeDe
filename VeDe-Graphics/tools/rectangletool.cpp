#include "rectangletool.h"
#include "properties/propertyfactory.h"
#include "commands/addgobjectcommand.h"
#include "commands/selectcommand.h" // TODO: remove
#include <QtMath>

gx::RectangleTool::RectangleTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Rectangle tool");
    QString start = "Place first corner";
    QString placeFirstCorner = "Placing a corner";
    QString moveEnd = "Place second corner";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(placeFirstCorner, STATE_DEF {
        m_anchorPoint = getCanvas()->getCursor();
        m_rect = std::make_shared<Rectangle>();
        m_rect->setTopLeft(m_anchorPoint);
        m_rect->setBottomRight(m_anchorPoint);
        PropertyFactory::setShapePreviewProperties(m_rect.get());

        gx::Command* command = new gx::AddGObjectCommand(m_rect, getCanvas());
        getCanvas()->executeCommand(command);
        getCanvas()->lock();

        m_rect->setGuiElement(true);
        moveToStateSilent(moveEnd);
    });

    addState(moveEnd, STATE_DEF {
        if(m_rect != nullptr) {
            moveEndPoint();
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finished, STATE_DEF {
        m_rect->copyPropertiesFrom(*this);
        m_rect->copyPropertiesFrom(*getCanvas());
        m_rect->updateProperties();
        m_rect->setGuiElement(false);

        getCanvas()->redraw(m_rect->boundingBox());
        getCanvas()->unlock();

        getCanvas()->clearSelectedObjects(false);
        getCanvas()->selectObject(m_rect);

        m_rect.reset();
        moveToStateSilent(start);
    });

    addTransition(start, UserEvent(MOUSE_PRESS, Qt::LeftButton), placeFirstCorner);
    addTransition(moveEnd, UserEvent(MOUSE_MOVE), moveEnd);
    addTransition(moveEnd, UserEvent(MOUSE_RELEASE, Qt::LeftButton), finished);

    setUpRestriction(STATE_DEF{
        if(m_rect != nullptr){
            moveEndPoint();
        }
    });

    moveToStateSilent(start);
}

void gx::RectangleTool::restrictPoints(const gx::Vertex& cursor, gx::Vertex &upLeft, gx::Vertex &downRight)
{
    float maxDist = qMax(qAbs(upLeft.x() - downRight.x()), qAbs(upLeft.y() - downRight.y()));

    if(cursor.x() < m_anchorPoint.x()) {
        upLeft.setX(m_anchorPoint.x() - maxDist);
    } else {
        downRight.setX(m_anchorPoint.x() + maxDist);
    }
    if(cursor.y() < m_anchorPoint.y()) {
        upLeft.setY(m_anchorPoint.y() - maxDist);
    } else {
        downRight.setY(m_anchorPoint.y() + maxDist);
    }
}

void gx::RectangleTool::moveEndPoint()
{
    Vertex cursor = getCanvas()->getCursor();
    Vertex upLeft(qMin(cursor.x(), m_anchorPoint.x()), qMin(cursor.y(), m_anchorPoint.y()));
    Vertex downRight(qMax(cursor.x(), m_anchorPoint.x()), qMax(cursor.y(), m_anchorPoint.y()));

    if(isRestricted()) {
        restrictPoints(cursor, upLeft, downRight);
    }

    //Disable buggy division by zero
    if (qAbs(downRight.x() - upLeft.x()) < 0.0001) {
        downRight.setX(downRight.x() + 0.0001);
    }
    if (qAbs(downRight.y() - upLeft.y()) < 0.0001) {
        downRight.setY(downRight.y() + 0.0001);
    }

    m_rect->setTopLeft(upLeft);
    m_rect->setBottomRight(downRight);

    getCanvas()->redraw();
}

