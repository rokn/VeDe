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
        m_anchorPoint = cursorPos;
        m_selection = QRectF(cursorPos.x(), cursorPos.y(), 1, 1);
        m_selecting = true;
        moveToStateSilent(moveSelect);
    });

    addState(moveSelect, STATE_DEF{
        Vertex cursor = getCanvas()->getCursor();
        Vertex upLeft(qMin(cursor.x(), m_anchorPoint.x()), qMin(cursor.y(), m_anchorPoint.y()));
        Vertex downRight(qMax(cursor.x(), m_anchorPoint.x()), qMax(cursor.y(), m_anchorPoint.y()));
        QRectF old = m_selection;
        m_selection.setTopLeft(Converters::toPoint(upLeft));
        m_selection.setBottomRight(Converters::toPoint(downRight));
        getCanvas()->redraw(m_selection.united(old));
    });

    addState(endSelect, STATE_DEF{
        moveToStateSilent(start);
        m_selecting = false;
        getCanvas()->redraw(m_selection);
    });

    addTransition(start, Transition(MOUSE_PRESS, Qt::LeftButton), selectStart);
    addTransition(moveSelect, Transition(MOUSE_MOVE), moveSelect);
    addTransition(moveSelect, Transition(MOUSE_RELEASE, Qt::LeftButton), endSelect);

    moveToStateSilent(start);
}

void gx::SelectTool::drawGui(CustomPainter &painter) const
{
    if(m_selecting)
    {
        painter.setStrokeColor(Color(0,0,0));
        painter.setBackColor(Color(0,0,0,0));
        painter.setStrokeWidth(1.0f / getCanvas()->getZoomFactor());
        painter.drawRectangle(m_selection.topLeft().x(), m_selection.topLeft().y(),
                               m_selection.bottomRight().x(), m_selection.bottomRight().y());
    }
}
