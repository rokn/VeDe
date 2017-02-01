#ifndef CANVAS_H
#define CANVAS_H

#include "tools/transition.h"
#include "objects/gobject.h"
#include "objects/rectangle.h"
#include "layer.h"
#include "commands/command.h"
#include <memory>
#include <QVector>
#include <QEvent>
#include <QRectF>

namespace gx
{
//Forward decl.
class Tool;

class Canvas : public PropertyHolder
{
//    Q_OBJECT
public:
    Canvas(std::shared_ptr<GObject> root = nullptr, QObject* parent = 0);
    virtual ~Canvas();

     /**
     * @brief Gets the root object of the canvas
     * @return The root GObject
     */
    std::shared_ptr<GObject> root();

    /**
     * @brief Get the mouse cursor positon relative to the canvas
     * @return A vertex containing the relative position
     */
    virtual Vertex getCursor() const = 0;

    /**
     * @brief Executes a command and stores it in the command list
     * @param The command to execute
     * @return Status code for result of the execution
     */
    int executeCommand(Command* command);

    /**
     * @brief Tries to undo the previous command from the stack
     * @return Status code for result of the undoing
     */
    int undoCommand();

    /**
     * @brief Tries to redo the next command from the stack
     * @return Status code for result of the redoing
     */
    int redoCommand();

    /**
     * @brief Gives the current tool a transition to handle
     * @param The transition to handle
     */
    void handleTransition(const Transition &transition);

    /**
     * @brief Simply redraws the whole canvas
     */
    virtual void redraw() = 0;
    virtual void redrawGui() = 0;
    virtual void redraw(QRectF area) = 0;

    /**
     * @brief Adds an object to the current active layer
     * @param The object to add
     */
    void addToCurrLayer(std::shared_ptr<GObject> object);

    /**
     * @brief Switches the current tool deactivating the previous
     * @param The new tool to activate
     */
    void changeCurrTool(Tool* newTool);

    std::shared_ptr<Layer> getCurrLayer() const;

    float getZoomFactor() const;
    void setZoomFactor(float zoomFactor);

    virtual void onAddObject(std::shared_ptr<GObject> object);

    Tool *getCurrTool() const;

private:
    std::shared_ptr<GObject> m_root;
    QVector<Command*> m_commandHistory;
    unsigned int m_currCommand;
    Tool* m_currTool;
    std::shared_ptr<Layer> m_currLayer;
    unsigned int m_idCount;
    float m_zoomFactor;
};
}

#endif // CANVAS_H
