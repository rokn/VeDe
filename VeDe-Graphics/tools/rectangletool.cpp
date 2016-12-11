#include "rectangletool.h"
#include "properties/propertyfactory.h"
#include "commands/addgobjectcommand.h"

gx::RectangleTool::RectangleTool(gx::Canvas *canvas)
    :Tool(canvas)
{
    setName("Rectangle tool");
    PropertyFactory::addShapeProperties(this);
    QString start = "Place first corner";
    QString placeFirstCorner = "Placing a corner";
    QString wait = "Place second corner";
    QString moveEnd = "Move second corner";
    QString finished = "Finished";

    addState(start, EMPTY_STATE);

    addState(placeFirstCorner, STATE_DEF {
        anchorPoint = getCanvas()->getCursor();
        m_rect = std::make_shared<Rectangle>();
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
            Vertex upLeft = m_rect->getUpLeft();
            Vertex downRight = m_rect->getDownRight();
            if(cursor.x() < anchorPoint.x()) {
                upLeft.setX(cursor.x());
                downRight.setX(anchorPoint.x());
            } else if (cursor.x() > anchorPoint.x()) {
                upLeft.setX(anchorPoint.x());
                downRight.setX(cursor.x());
            } else {
                upLeft.setX(cursor.x());
                downRight.setX(cursor.x());
            }

            if(cursor.y() < anchorPoint.y()) {
                upLeft.setY(cursor.y());
                downRight.setY(anchorPoint.y());
            } else if (cursor.y() > anchorPoint.y()) {
                upLeft.setY(anchorPoint.y());
                downRight.setY(cursor.y());
            } else {
                upLeft.setY(cursor.y());
                downRight.setY(cursor.y());
            }

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
