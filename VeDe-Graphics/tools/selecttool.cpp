#include "selecttool.h"
#include "commonstates.h"
#include "converters.h"
#include "commands/selectcommand.h"
#include "commands/translatecommand.h"
#include "color.h"
#include <QtMath>
#include <QDebug>

gx::SelectTool::SelectTool(Canvas *canvas)
    :Tool(canvas)
{
    setName("Select Tool");
    QString start = "Select items";
    QString rotatePreStart = "Start rotation";
    QString rotateStart = "Starting rotation";
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
        m_anchorPoint = cursorPos;

        if(getCanvas()->isKeyPressed(Qt::Key_Shift) && getCanvas()->isKeyPressed(Qt::Key_R)){
            m_rotating = true;
            m_useRotAxis = true;
            m_rotationAxis = Converters::toVertex(getCanvas()->getSelectedObjectsBox().center());
            m_oldAngleSet = false;
        }

        auto list = getCanvas()->getSelectedObjects();
        foreach(auto obj, list) {
            if(obj->containsPoint(cursorPos)) {
                if(getCanvas()->isKeyPressed(Qt::Key_R)){
                    m_rotating = true;
                    m_useRotAxis = false;
                    m_oldAngleSet = false;
                    break;
                } else {
                    m_translating = true;
                    m_startTranslation = cursorPos;
                    break;
                }
            }
        }

        if(!m_translating && !m_rotating) {
            m_selection = QRectF(cursorPos.x(), cursorPos.y(), 1, 1);
            m_selecting = true;
        }
        //TODO: OPTIMIZE!!

        moveToStateSilent(moveSelect);
    });

    addState(moveSelect, STATE_DEF{
        Vertex cursor = getCanvas()->getCursor();

        if(m_selecting) {
            updateSelection(cursor);
        } else if (m_translating) {
            updateTranslation(cursor);
        } else if (m_rotating) {
            updateRotation(cursor);
        }
    });

    addState(endSelect, STATE_DEF{
        if(m_selecting) {
            endSelection();
        } else if (m_translating) {
            endTranslation();
        } else if (m_rotating) {
            endRotation();
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
        painter.setStrokeWidth(getCanvas()->mapValueToZoom(1.0));
        painter.drawRectangle(m_selection.topLeft().x(), m_selection.topLeft().y(),
                               m_selection.bottomRight().x(), m_selection.bottomRight().y());
    } else if (m_rotating) {
        painter.setStrokeColor(Color(0,255,0));
        painter.setBackColor(Color(0,0,0,0));
        painter.setStrokeWidth(getCanvas()->mapValueToZoom(1.0));
        painter.drawLine(m_anchorPoint, m_oldPosition);
    }
}

void gx::SelectTool::selectObjects(QRectF rect)
{
    auto currLayerObjects = getCanvas()->getCurrLayer()->getChildren();
    QRectF redrawBox;
    QList<SharedGObject> selectedObjects;

    foreach (auto& obj, currLayerObjects) {
        if(rect.contains(obj->boundingBox())) {
            selectedObjects.append(obj);
        }
    }

    if(selectedObjects.size() > 0){
        if(!m_union){
            getCanvas()->clearSelectedObjects();
        }

        CanvasCommand* command = new SelectCommand();
        command->setCanvas(getCanvas());
        command->setObjects(selectedObjects);
        getCanvas()->executeCommand(command);
    }
}

void gx::SelectTool::updateSelection(gx::Vertex cursor)
{
    Vertex upLeft(qMin(cursor.x(), m_anchorPoint.x()), qMin(cursor.y(), m_anchorPoint.y()));
    Vertex downRight(qMax(cursor.x(), m_anchorPoint.x()), qMax(cursor.y(), m_anchorPoint.y()));
    QRectF old = m_selection;
    m_selection.setTopLeft(Converters::toPoint(upLeft));
    m_selection.setBottomRight(Converters::toPoint(downRight));
    getCanvas()->redraw(m_selection.united(old));
}

void gx::SelectTool::updateTranslation(gx::Vertex cursor)
{
    auto objects = getCanvas()->getSelectedObjects();
    QRectF redrawRect;

    foreach(auto obj, objects) {
        redrawRect = redrawRect.united(obj->boundingBox());
        obj->translate(Vertex(cursor.x() - m_anchorPoint.x(), cursor.y() - m_anchorPoint.y()));
        redrawRect = redrawRect.united(obj->boundingBox());
    }

    m_anchorPoint = cursor;
    getCanvas()->redraw(redrawRect);
}

void gx::SelectTool::updateRotation(gx::Vertex cursor)
{
    Vertex normCursor = (cursor - m_anchorPoint).normalized();
    double currAngle = qRadiansToDegrees(qAtan2(normCursor.y(), normCursor.x()));

    if(m_oldAngleSet) {
        auto objects = getCanvas()->getSelectedObjects();
        if (m_useRotAxis) {
            foreach(auto obj, objects) {
                obj->rotate(currAngle - m_oldAngle, QTransform::fromTranslate(m_rotationAxis.x(), m_rotationAxis.y()));
            }
        } else {
            foreach(auto obj, objects) {
                obj->rotate(currAngle - m_oldAngle);
            }
        }
    } else {
        m_oldAngleSet = true;
    }

    m_oldAngle = currAngle;
    m_oldPosition = cursor;
    getCanvas()->redraw();//TODO: optimize
}

void gx::SelectTool::endSelection()
{
    m_selecting = false;
    selectObjects(m_selection);
    getCanvas()->redraw(m_selection);
}

void gx::SelectTool::endTranslation()
{
    m_translating = false;
    CanvasCommand *translateCommand = new TranslateCommand(getCanvas()->getCursor() - m_startTranslation);
    translateCommand->setCanvas(getCanvas());
    translateCommand->setObjects(getCanvas()->getSelectedObjects());
    getCanvas()->addSilentCommand(translateCommand);
}

void gx::SelectTool::endRotation()
{
    m_rotating = false;
    getCanvas()->redraw();
}
