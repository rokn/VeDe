#include "selecttool.h"
#include "converters.h"
#include "commands/selectcommand.h"
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
    QString unionEnable = "Union enable";
    QString unionDisable = "Union disable";
    QString clearSelection = "Clear selection";
    m_selecting = false;
    m_union = false;

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
        selectObjects(m_selection);
        getCanvas()->redraw(m_selection);
    });

    addState(unionEnable, STATE_DEF{
        m_union = true;
        moveToStateSilent(getLastState());
    });

    addState(unionDisable, STATE_DEF{
        m_union = false;
        moveToStateSilent(getLastState());
    });

    addState(clearSelection, STATE_DEF{
        if(m_selecting){
            m_selecting = false;
            getCanvas()->redraw(m_selection);
        }

        getCanvas()->clearSelectedObjects();
        moveToStateSilent(start);
    });

    addTransition(start, UserEvent(MOUSE_PRESS, Qt::LeftButton), selectStart);
    addTransition(moveSelect, UserEvent(MOUSE_MOVE), moveSelect);
    addTransition(moveSelect, UserEvent(MOUSE_RELEASE, Qt::LeftButton), endSelect);
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_Shift), unionEnable);
    addTransition(ANY_STATE, UserEvent(KEY_RELEASE, Qt::Key_Shift), unionDisable);
    addTransition(ANY_STATE, UserEvent(MOUSE_PRESS, Qt::RightButton), clearSelection);
    addTransition(ANY_STATE, UserEvent(KEY_RELEASE, Qt::Key_Escape), clearSelection);

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

void gx::SelectTool::selectObjects(QRectF rect)
{
    auto currLayerObjects = getCanvas()->getCurrLayer()->getChildren();
    QRectF redrawBox;
    QList<std::shared_ptr<GObject>> selectedObjects;

    foreach (auto& obj, currLayerObjects) {
        if(rect.contains(obj->boundingBox())) {
            selectedObjects.append(obj);
        }
    }

    if(selectedObjects.size() > 0){
        if(!m_union){
            getCanvas()->clearSelectedObjects();
        }

        Command* command = new SelectCommand(selectedObjects, getCanvas());
        getCanvas()->executeCommand(command);
    }
}
