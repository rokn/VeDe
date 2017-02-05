#include "selecttool.h"
#include "converters.h"
#include "color.h"
#include <QtMath>

gx::SelectTool::SelectTool(Canvas *canvas)
    :Tool(canvas)
{
    setName("Select Tool");
    QString start = "Select items";
    QString selectStart = "Started selection";
    QString moveSelect = "Move selection";
    QString endSelect = "Ending selection";
    m_selecting = false;

    addState(start, EMPTY_STATE);
    addState(selectStart, STATE_DEF{
        Vertex cursorPos = getCanvas()->getCursor();
        m_selection = QRectF(cursorPos.x(), cursorPos.y(), 1, 1);
        m_selecting = true;
        moveToStateSilent(moveSelect);
    });

    addState(moveSelect, STATE_DEF{
        Vertex cursor = getCanvas()->getCursor();
        Vertex upLeft(qMin(cursor.x(), m_anchorPoint.x()), qMin(cursor.y(), m_anchorPoint.y()));
        Vertex downRight(qMax(cursor.x(), m_anchorPoint.x()), qMax(cursor.y(), m_anchorPoint.y()));
        m_selection.setTopLeft(Converters::toPoint(upLeft));
        m_selection.setBottomRight(Converters::toPoint(downRight));
        getCanvas()->redrawGui();
    });

    addState(endSelect, STATE_DEF{
        moveToStateSilent(start);
        m_selecting = false;
        getCanvas()->redrawGui();
    });

    addTransition(start, Transition(MOUSE_PRESS, Qt::LeftButton), selectStart);
    addTransition(moveSelect, Transition(MOUSE_MOVE), moveSelect);
    addTransition(moveSelect, Transition(MOUSE_RELEASE, Qt::LeftButton), endSelect);

    moveToStateSilent(start);
}

void gx::SelectTool::drawGui(gx::CustomPainter *painter) const
{
    if(m_selecting)
    {
        painter->setStrokeColor(Color(0,0,0));
        painter->setBackColor(Color(0,0,0,0));
        painter->setStrokeWidth(1.0f / getCanvas()->getZoomFactor());
        painter->drawRectangle(m_selection.topLeft().x(), m_selection.topLeft().y(),
                               m_selection.bottomRight().x(), m_selection.bottomRight().y());
    }
}
