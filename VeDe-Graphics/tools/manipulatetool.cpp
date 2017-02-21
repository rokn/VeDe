#include "manipulatetool.h"
#include "commonstates.h"
#include "converters.h"
#include "commands/selectcommand.h"
#include "commands/translatecommand.h"
#include "commands/rotatecommand.h"
#include "commands/scalecommand.h"
#include "color.h"
#include <QtMath>
#include <QDebug>

gx::ManipulateTool::ManipulateTool(Canvas *canvas)
    :Tool(canvas)
{
    setName("Manipulate Tool");
    QString start = "Select items";
    QString changeMode = "Changiong mode";
    QString modeStart = "Starting mode";
    QString modeUpdate = "Update manipulation";
    QString endMode = "Ending mode";
    QString unionEnable = "Union enable";
    QString unionDisable = "Union disable";
    QString deleteObjects = "Delete objects";
    QString selectAll = "Select all";
    QString deselectAll = "Deselect all";

//    m_union = false;
    m_inManipulation = false;

    m_currMode = new SelectionMode();
    m_currMode->setCanvas(getCanvas());

    addState(start, EMPTY_STATE);

    addState(changeMode, STATE_DEF{
         ManipulateMode *newMode = nullptr;
         switch(t.key()) {
            case Qt::Key_Q:
                 newMode = new SelectionMode;
                 break;
            case Qt::Key_W:
                 newMode = new TranslationMode;
                 break;
            case Qt::Key_E:
                 newMode = new RotationMode;
                 break;
            case Qt::Key_R:
                 newMode = new ScaleMode;
                 break;
            default:break;
         }
         if(newMode != nullptr) {
             delete m_currMode;
             m_currMode = newMode;
             m_currMode->setCanvas(getCanvas());
         }
         moveToStateSilent(getLastState());
    });

    addState(modeStart, STATE_DEF{
        Vertex cursor = getCanvas()->getCursor();

        m_inManipulation = true;
        m_currMode->startManipulation(cursor);

        moveToStateSilent(modeUpdate);
    });

    addState(modeUpdate, STATE_DEF{
        Vertex cursor = getCanvas()->getCursor();

        auto objects = getCanvas()->getSelectedObjects();
        QRectF redrawRect;

        foreach(auto obj, objects) {
            redrawRect = redrawRect.united(obj->boundingBox());
            m_currMode->updateManipulation(cursor, obj);
            redrawRect = redrawRect.united(obj->boundingBox());
        }
        getCanvas()->redraw(redrawRect);

        m_currMode->postUpdate(cursor);
    });

    addState(endMode, STATE_DEF{
        auto command = m_currMode->endManipulation();
        if(command != nullptr) {
            command->setCanvas(getCanvas());
            command->setObjects(getCanvas()->getSelectedObjects());
            getCanvas()->addSilentCommand(command);
        }
        m_inManipulation = false;

        moveToStateSilent(start);
    });

    addState(unionEnable, STATE_DEF{
//        m_union = true;
        moveToStateSilent(getLastState());
    });

    addState(unionDisable, STATE_DEF{
//        m_union = false;
        moveToStateSilent(getLastState());
    });

    addState(deleteObjects, CommonStates::deleteSelectedObjects(this));
    addState(selectAll, CommonStates::selectAllOnCurrLayer(this));
    addState(deselectAll, CommonStates::deselectAll(this));

    addTransition(start, UserEvent(MOUSE_PRESS, Qt::LeftButton), modeStart);
    addTransition(modeUpdate, UserEvent(MOUSE_MOVE), modeUpdate);
    addTransition(modeUpdate, UserEvent(MOUSE_RELEASE, Qt::LeftButton), endMode);
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_Shift), unionEnable);
    addTransition(ANY_STATE, UserEvent(KEY_RELEASE, Qt::Key_Shift), unionDisable);

    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_Delete), deleteObjects);
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_A), selectAll);
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_Escape), deselectAll);

    addTransition(start, UserEvent(KEY_PRESS, Qt::Key_Q), changeMode);
    addTransition(start, UserEvent(KEY_PRESS, Qt::Key_W), changeMode);
    addTransition(start, UserEvent(KEY_PRESS, Qt::Key_E), changeMode);
    addTransition(start, UserEvent(KEY_PRESS, Qt::Key_R), changeMode);

    moveToStateSilent(start);
}

gx::ManipulateTool::~ManipulateTool()
{
    delete m_currMode;
}

void gx::ManipulateTool::drawGui(CustomPainter &painter) const
{
    if (m_inManipulation) {
        m_currMode->drawGui(painter);
    }
}


void gx::ManipulateTool::TranslationMode::startManipulation(gx::Vertex cursor)
{
    m_startPosition = cursor;
    m_lastPosition = cursor;
}

void gx::ManipulateTool::TranslationMode::updateManipulation(gx::Vertex cursor, SharedGObject obj)
{
    obj->translate(cursor - m_lastPosition);
}

void gx::ManipulateTool::TranslationMode::postUpdate(gx::Vertex cursor)
{
    m_lastPosition = cursor;
}

gx::CanvasCommand *gx::ManipulateTool::TranslationMode::endManipulation()
{
    return new TranslateCommand(m_lastPosition - m_startPosition);
}

void gx::ManipulateTool::ManipulateMode::drawGui(gx::CustomPainter &painter) const{}

gx::Canvas *gx::ManipulateTool::ManipulateMode::getCanvas()
{
    return m_canvas;
}

gx::Canvas *gx::ManipulateTool::ManipulateMode::getCanvas() const
{
    return m_canvas;
}

void gx::ManipulateTool::ManipulateMode::setCanvas(gx::Canvas *canvas)
{
    m_canvas = canvas;
}

void gx::ManipulateTool::SelectionMode::startManipulation(gx::Vertex cursor)
{
    m_anchorPoint = cursor;
}

void gx::ManipulateTool::SelectionMode::updateManipulation(gx::Vertex cursor, gx::SharedGObject obj)
{
}

void gx::ManipulateTool::SelectionMode::postUpdate(gx::Vertex cursor)
{
    Vertex upLeft(qMin(cursor.x(), m_anchorPoint.x()), qMin(cursor.y(), m_anchorPoint.y()));
    Vertex downRight(qMax(cursor.x(), m_anchorPoint.x()), qMax(cursor.y(), m_anchorPoint.y()));
    QRectF old = m_selection;
    m_selection.setTopLeft(Converters::toPoint(upLeft));
    m_selection.setBottomRight(Converters::toPoint(downRight));
    getCanvas()->redraw(m_selection.united(old)); //TODO: must redraw think
}

gx::CanvasCommand *gx::ManipulateTool::SelectionMode::endManipulation()
{
    auto currLayerObjects = getCanvas()->getCurrLayer()->getChildren();
    QList<SharedGObject> selectedObjects;

    foreach (auto& obj, currLayerObjects) {
        if(m_selection.contains(obj->boundingBox())) {
            selectedObjects.append(obj);
        }
    }

    if(selectedObjects.size() > 0){
        if(!getCanvas()->isKeyPressed(Qt::Key_Shift)) {
            getCanvas()->clearSelectedObjects();
        }

        CanvasCommand* command = new SelectCommand();
        command->setCanvas(getCanvas());
        command->setObjects(selectedObjects);
        getCanvas()->executeCommand(command);
    }

    getCanvas()->redraw(m_selection);

    return nullptr;
}

void gx::ManipulateTool::SelectionMode::drawGui(gx::CustomPainter &painter) const
{
    painter.setStrokeColor(Color(0,0,0));
    painter.setBackColor(Color(0,0,0,0));
    painter.setStrokeWidth(getCanvas()->mapValueToZoom(1.0));
    painter.drawRectangle(m_selection.topLeft().x(), m_selection.topLeft().y(),
                           m_selection.bottomRight().x(), m_selection.bottomRight().y());
}

void gx::ManipulateTool::RotationMode::startManipulation(gx::Vertex cursor)
{
    if (getCanvas()->isKeyPressed(Qt::Key_Shift)) {
        m_useRotAxis = true;
        m_rotationAxis = Converters::toVertex(getCanvas()->getSelectedObjectsBox().center());
    } else {
        m_useRotAxis = false;
    }

    m_oldAngle = 0.0;
    m_totalRotation = 0.0;
    m_startPosition = cursor;
}

void gx::ManipulateTool::RotationMode::updateManipulation(gx::Vertex cursor, gx::SharedGObject obj) //TODO: Find a way to not calculate every time(maybe preUpdate())
{
    Vertex normCursor = (cursor - m_startPosition).normalized();
    double currAngle = qRadiansToDegrees(qAtan2(normCursor.y(), normCursor.x()));

    double rotation = currAngle - m_oldAngle;

    if (m_useRotAxis) {
        obj->rotate(rotation, QTransform::fromTranslate(m_rotationAxis.x(), m_rotationAxis.y()));
    } else {
        obj->rotate(rotation);
    }
}

void gx::ManipulateTool::RotationMode::postUpdate(gx::Vertex cursor)
{
    Vertex normCursor = (cursor - m_startPosition).normalized();
    double currAngle = qRadiansToDegrees(qAtan2(normCursor.y(), normCursor.x()));

    m_totalRotation += currAngle - m_oldAngle;

    m_oldAngle = currAngle;
    m_oldPosition = cursor;
    getCanvas()->redraw();//TODO: optimize
}

gx::CanvasCommand *gx::ManipulateTool::RotationMode::endManipulation()
{
    CanvasCommand *rotateCommand;

    if(m_useRotAxis) {
         rotateCommand = new RotateCommand(m_totalRotation, m_rotationAxis);
    } else {
        rotateCommand = new RotateCommand(m_totalRotation);
    }

    getCanvas()->redraw();//TODO: optimize

    return rotateCommand;
}

void gx::ManipulateTool::RotationMode::drawGui(gx::CustomPainter &painter) const
{
    painter.setBackColor(Color(0,0,0,0));
    painter.setStrokeWidth(getCanvas()->mapValueToZoom(1.0));

    painter.setStrokeColor(Color(0,0,255));
    double radius = getCanvas()->mapValueToZoom(50.0);
    painter.drawEllipse(m_startPosition, Vertex(radius, radius));
    painter.drawLine(m_startPosition, Vertex(m_startPosition.x() + radius, m_startPosition.y()));

    painter.setStrokeColor(Color(0,255,0));
    Vertex endPoint = (m_oldPosition - m_startPosition).normalized() * radius;
    painter.drawLine(m_startPosition, m_startPosition + endPoint);
}

void gx::ManipulateTool::ScaleMode::startManipulation(gx::Vertex cursor)
{
    m_startPosition = cursor;
    m_oldPosition = cursor;
    m_startBox = getCanvas()->getSelectedObjectsBox();
}

void gx::ManipulateTool::ScaleMode::updateManipulation(gx::Vertex cursor, gx::SharedGObject obj)
{
    QRectF box = getCanvas()->getSelectedObjectsBox();
    Vertex diffOld = (m_oldPosition - m_startPosition);
    Vertex diffNew = (cursor - m_startPosition);
    Vertex scale;
    scale.setX(diffNew.x() - diffOld.x());
    scale.setY(diffNew.y() - diffOld.y());
    double widthScale = (box.width() + scale.x()) / box.width();
    double heightScale = (box.height() + scale.y()) / box.height();

    obj->scale(Vertex(widthScale, heightScale));
}

void gx::ManipulateTool::ScaleMode::postUpdate(gx::Vertex cursor)
{
    m_oldPosition = cursor;
    getCanvas()->redraw();
}

gx::CanvasCommand *gx::ManipulateTool::ScaleMode::endManipulation()
{
    Vertex diff = m_oldPosition - m_startPosition;
    double widthScale = (m_startBox.width() + diff.x()) / m_startBox.width();
    double heightScale = (m_startBox.height() + diff.y()) / m_startBox.height();
    getCanvas()->redraw();
    return new ScaleCommand(Vertex(widthScale, heightScale));
}

void gx::ManipulateTool::ScaleMode::drawGui(gx::CustomPainter &painter) const
{
    painter.setBackColor(Color(0,0,0,0));
    painter.setStrokeWidth(getCanvas()->mapValueToZoom(1.0));

    painter.setStrokeColor(Color(0,255,0));
    painter.drawLine(m_startPosition, Vertex(m_startPosition.x(), m_oldPosition.y()));

    painter.setStrokeColor(Color(0,0,255));
    painter.drawLine(m_startPosition, Vertex(m_oldPosition.x(), m_startPosition.y()));
}
