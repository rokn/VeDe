#include "manipulatetool.h"
#include "commonstates.h"
#include "converters.h"
#include "commands/selectcommand.h"
#include "commands/translatecommand.h"
#include "commands/rotatecommand.h"
#include "color.h"
#include <QtMath>
#include <QDebug>

gx::ManipulateTool::ManipulateTool(Canvas *canvas)
    :Tool(canvas)
{
    setName("Manipulate Tool");
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
    m_totalRotation = 0.0;

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

    addState("Scal", STATE_DEF{
        auto objects = getCanvas()->getSelectedObjects();
        QRectF redrawRect;

        foreach(auto obj, objects) {
            redrawRect = redrawRect.united(obj->boundingBox());
            obj->scale(Vertex(1.1, 1.), QTransform::fromTranslate(obj->boundingBox().x() + obj->boundingBox().width(), obj->boundingBox().center().y()));
            redrawRect = redrawRect.united(obj->boundingBox());
        }

        getCanvas()->redraw(redrawRect);
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
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_S), "Scal");

    moveToStateSilent(start);
}

void gx::ManipulateTool::drawGui(CustomPainter &painter) const
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

void gx::ManipulateTool::selectObjects(QRectF rect)
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

void gx::ManipulateTool::updateSelection(gx::Vertex cursor)
{
    Vertex upLeft(qMin(cursor.x(), m_anchorPoint.x()), qMin(cursor.y(), m_anchorPoint.y()));
    Vertex downRight(qMax(cursor.x(), m_anchorPoint.x()), qMax(cursor.y(), m_anchorPoint.y()));
    QRectF old = m_selection;
    m_selection.setTopLeft(Converters::toPoint(upLeft));
    m_selection.setBottomRight(Converters::toPoint(downRight));
    getCanvas()->redraw(m_selection.united(old));
}

void gx::ManipulateTool::updateTranslation(gx::Vertex cursor)
{
}

void gx::ManipulateTool::updateRotation(gx::Vertex cursor)
{
    Vertex normCursor = (cursor - m_anchorPoint).normalized();
    double currAngle = qRadiansToDegrees(qAtan2(normCursor.y(), normCursor.x()));

    if(m_oldAngleSet) {
        auto objects = getCanvas()->getSelectedObjects();
        double rotation = currAngle - m_oldAngle;
        if (m_useRotAxis) {
            foreach(auto obj, objects) {
                obj->rotate(rotation, QTransform::fromTranslate(m_rotationAxis.x(), m_rotationAxis.y()));
            }
        } else {
            foreach(auto obj, objects) {
                obj->rotate(rotation);
            }
        }

        m_totalRotation += rotation;
    } else {
        m_oldAngleSet = true;
    }

    m_oldAngle = currAngle;
    m_oldPosition = cursor;
    getCanvas()->redraw();//TODO: optimize
}

void gx::ManipulateTool::endSelection()
{
    m_selecting = false;
    selectObjects(m_selection);
    getCanvas()->redraw(m_selection);
}

void gx::ManipulateTool::endTranslation()
{
    m_translating = false;
    CanvasCommand *translateCommand = new TranslateCommand(getCanvas()->getCursor() - m_startTranslation);
    translateCommand->setCanvas(getCanvas());
    translateCommand->setObjects(getCanvas()->getSelectedObjects());
    getCanvas()->addSilentCommand(translateCommand);
}

void gx::ManipulateTool::endRotation()
{
    m_rotating = false;
    CanvasCommand *rotateCommand;
    if(m_useRotAxis) {
         rotateCommand = new RotateCommand(m_totalRotation, m_rotationAxis);
    } else {
        rotateCommand = new RotateCommand(m_totalRotation);
    }
    rotateCommand->setCanvas(getCanvas());
    rotateCommand->setObjects(getCanvas()->getSelectedObjects());
    getCanvas()->addSilentCommand(rotateCommand);
    getCanvas()->redraw();
    m_totalRotation = 0.0;
}


void gx::ManipulateTool::TranslationMode::startManipulation(gx::Vertex cursor)
{
    m_startPosition = cursor;
    m_lastPosition = cursor;
}

void gx::ManipulateTool::TranslationMode::updateManipulation(gx::Vertex cursor)
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

Qt::Key gx::ManipulateTool::ManipulateMode::getEnterKey() const
{
    return m_enterKey
}
