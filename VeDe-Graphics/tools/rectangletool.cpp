#include "rectangletool.h"
#include "commands/addgobjectcommand.h"

gx::RectangleTool::RectangleTool(gx::Canvas *canvas)
    :Tool(canvas)
{
    uint start = addState("Place first corner", EMPTY_STATE);

    uint placeFirstCorner = addState("Placing corner", [this](QEvent const&e)->int{
        anchorPoint = getCanvas()->getCursor();
        m_rect = std::make_shared<Rectangle>();
        m_rect->setUpLeft(anchorPoint);
        m_rect->setDownRight(anchorPoint);

        gx::Command* command = new gx::AddGObjectCommand(m_rect, getCanvas());
        getCanvas()->executeCommand(command);
        return 2;
    });

    uint wait = addState("Place second corner", EMPTY_STATE);

    uint moveEnd = addState("Move second corner", [this](QEvent const& e)->int{
            //TODO: Strange behaviour when moving mouse fast
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
            return 2;
        }
        return 0;
    });

    uint finish = addState("Finihed", [](QEvent const&e)->int{
        return 0;
    });

    addTransition(start, QEvent::MouseButtonPress, placeFirstCorner);
    addTransition(wait, QEvent::MouseMove, moveEnd);
    addTransition(wait, QEvent::MouseButtonPress, finish);
}
