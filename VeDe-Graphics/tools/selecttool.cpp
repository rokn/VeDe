#include "selecttool.h"
#include "commonstates.h"
#include "converters.h"
#include "commands/selectcommand.h"
#include "color.h"
#include <QtMath>
#include <QDebug>

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
    QString deleteObjects = "Delete objects";
    QString selectAll = "Select all";
    QString deselectAll = "Deselect all";
    m_selecting = false;
    m_union = false;

    addState(start, EMPTY_STATE);
    addState(selectStart, STATE_DEF{
        Vertex cursorPos = getCanvas()->getCursor();

        auto list = getCanvas()->getSelectedObjects();
        foreach(auto obj, list) {
            if(obj->containsPoint(cursorPos)) {
                m_dragging = true;
                break;
            }
        }

        m_anchorPoint = cursorPos;
        if(!m_dragging) {
            m_selection = QRectF(cursorPos.x(), cursorPos.y(), 1, 1);
            m_selecting = true;
        }

        moveToStateSilent(moveSelect);
    });

    addState(moveSelect, STATE_DEF{
        Vertex cursor = getCanvas()->getCursor();

        if(m_selecting) {
            Vertex upLeft(qMin(cursor.x(), m_anchorPoint.x()), qMin(cursor.y(), m_anchorPoint.y()));
            Vertex downRight(qMax(cursor.x(), m_anchorPoint.x()), qMax(cursor.y(), m_anchorPoint.y()));
            QRectF old = m_selection;
            m_selection.setTopLeft(Converters::toPoint(upLeft));
            m_selection.setBottomRight(Converters::toPoint(downRight));
            getCanvas()->redraw(m_selection.united(old));
        } else if (m_dragging) {
            auto objects = getCanvas()->getSelectedObjects();
            foreach(auto obj, objects) {
                QTransform t = obj->getTransform();
                t.translate(cursor.x() - m_anchorPoint.x(), cursor.y() - m_anchorPoint.y());
                obj->setTransform(t);
            }
            m_anchorPoint = cursor;
        }
    });

    addState(endSelect, STATE_DEF{
        if(m_selecting) {
            m_selecting = false;
            selectObjects(m_selection);
            getCanvas()->redraw(m_selection);
        } else if (m_dragging) {
            m_dragging = false;
        }
        moveToStateSilent(start);
    });

    addState(unionEnable, STATE_DEF{
        m_union = true;
        moveToStateSilent(getLastState());
    });

    addState(unionDisable, STATE_DEF{
        m_union = false;
        moveToStateSilent(getLastState());
    });

    addState(deleteObjects, CommonStates::deleteSelectedObjects(this));
    addState(selectAll, CommonStates::selectAllOnCurrLayer(this));
    addState(deselectAll, CommonStates::deselectAll(this));

    addTransition(start, UserEvent(MOUSE_PRESS, Qt::LeftButton), selectStart);
    addTransition(moveSelect, UserEvent(MOUSE_MOVE), moveSelect);
    addTransition(moveSelect, UserEvent(MOUSE_RELEASE, Qt::LeftButton), endSelect);
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_Shift), unionEnable);
    addTransition(ANY_STATE, UserEvent(KEY_RELEASE, Qt::Key_Shift), unionDisable);

    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_Delete), deleteObjects);
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_A), selectAll);
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_Escape), deselectAll);
    addTransition(ANY_STATE, UserEvent(MOUSE_PRESS, Qt::RightButton), deselectAll);

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
