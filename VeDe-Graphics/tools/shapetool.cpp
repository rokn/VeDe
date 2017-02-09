#include "shapetool.h"
#include "commonstates.h"
#include "properties/propertynames.h"
#include "properties/propertyfactory.h"
#include "commands/addgobjectcommand.h"

gx::ShapeTool::ShapeTool(gx::Canvas *canvas)
    :RestrictableTool(canvas)
{
    addProperty(PROP::STROKE_WIDTH, PROP_FLOAT)->toFloat() = 1.0f;
    m_startState = "Start";
    m_placeFirstState = "Starting a shape";
    m_moveState = "Move control";
    m_finishedState = "Finished";
}

void gx::ShapeTool::initStates(bool includeTransitions)
{
    QString deleteObjects = "Delete objects";
    QString selectAll = "Select all";
    QString deselectAll = "Deselect all";

    addState(m_startState, EMPTY_STATE);

    addState(m_placeFirstState, STATE_DEF {
        bool move = startShape(getCanvas()->getCursor());

        if(m_shape != nullptr){
            PropertyFactory::setShapePreviewProperties(m_shape.get());

            Command* command = new AddGObjectCommand(m_shape, getCanvas());
            getCanvas()->executeCommand(command);
            getCanvas()->lock();

            m_shape->setGuiElement(true);

            if(move){
                moveToStateSilent(m_moveState);
            }
        }
    });

    addState(m_moveState, STATE_DEF {
        if(m_shape != nullptr) {
            moveControl(getCanvas()->getCursor());
        } else {
            moveToStateSilent(m_startState);
        }
    });

    addState(m_finishedState, STATE_DEF {
        if(m_shape != nullptr) {
            m_shape->copyPropertiesFrom(*this);
            m_shape->copyPropertiesFrom(*getCanvas());
            m_shape->updateProperties();
            m_shape->setGuiElement(false);

            getCanvas()->redraw(m_shape->boundingBox());
            getCanvas()->unlock();

            getCanvas()->clearSelectedObjects(false);
            getCanvas()->selectObject(m_shape);

            m_shape.reset();
        }

        moveToStateSilent(m_startState);
    });

    addState(deleteObjects, CommonStates::deleteSelectedObjects(this));
    addState(selectAll, CommonStates::selectAllOnCurrLayer(this));
    addState(deselectAll, CommonStates::deselectAll(this));

    if(includeTransitions) {
        addTransition(m_moveState, UserEvent(MOUSE_MOVE), m_moveState);
        addTransition(m_moveState, UserEvent(MOUSE_RELEASE, Qt::LeftButton), m_finishedState);
    }

    addTransition(m_startState, UserEvent(MOUSE_PRESS, Qt::LeftButton), m_placeFirstState);
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_Delete), deleteObjects);
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_A), selectAll);
    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_Escape), deselectAll);

    setUpRestriction(STATE_DEF{
        if(m_shape != nullptr){
            moveControl(getCanvas()->getCursor());
        }
    });

    moveToStateSilent(m_startState);
}

void gx::ShapeTool::setShape(const std::shared_ptr<Shape> &shape)
{
    m_shape = shape;
}

bool gx::ShapeTool::startShape(gx::Vertex mousePos)
{
    return true;
}

void gx::ShapeTool::moveControl(gx::Vertex mousePos)
{
}
