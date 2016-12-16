#include "rectangletool.h"
#include "commands/addgobjectcommand.h"
#include <QtMath>

gx::RectangleTool::RectangleTool(gx::Canvas *canvas)
    :ShapeTool(canvas)
{
    setName("Rectangle tool");
    QString start = "Place first corner";
    QString placeFirstCorner = "Placing a corner";
    QString wait = "Place second corner";
    QString moveEnd = "Move second corner";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(placeFirstCorner, STATE_DEF {
        anchorPoint = getCanvas()->getCursor();
        m_rect = std::make_shared<Rectangle>();
        m_rect->copyPropertiesFrom(*this);
        m_rect->copyPropertiesFrom(*getCanvas());
        m_rect->setUpLeft(anchorPoint);
        m_rect->setDownRight(anchorPoint);

        gx::Command* command = new gx::AddGObjectCommand(m_rect, getCanvas());
        getCanvas()->executeCommand(command);
        moveToStateSilent(wait);
    });

    addState(wait, EMPTY_STATE);

    addState(moveEnd, STATE_DEF {
        if(m_rect != nullptr) {
            Vertex cursor = getCanvas()->getCursor();
            Vertex upLeft(qMin(cursor.x(), anchorPoint.x()), qMin(cursor.y(), anchorPoint.y()));
            Vertex downRight(qMax(cursor.x(), anchorPoint.x()), qMax(cursor.y(), anchorPoint.y()));

            m_rect->setUpLeft(upLeft);
            m_rect->setDownRight(downRight);

            getCanvas()->redraw();

            moveToStateSilent(wait);
        } else {
            moveToStateSilent(start);
        }
    });

    addState(finished, STATE_DEF {
        moveToStateSilent(start);
    });

    addTransition(start, Transition(QEvent::MouseButtonPress, Qt::LeftButton), placeFirstCorner);
    addTransition(wait, Transition(QEvent::MouseMove), moveEnd);
    addTransition(wait, Transition(QEvent::MouseButtonPress, Qt::LeftButton), finished);

    moveToStateSilent(start);
}

void gx::RectangleTool::restrictPoints(gx::Vertex &upLeft, gx::Vertex &downRight)
{
}

