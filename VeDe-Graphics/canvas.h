#ifndef CANVAS_H
#define CANVAS_H

#include "tools/transition.h"
#include "objects/gobject.h"
#include "layer.h"
#include "commands/command.h"
#include <memory>
#include <QVector>
#include <QEvent>

namespace gx
{
//Forward decl.
class Tool;

class Canvas : public PropertyHolder
{
    Q_OBJECT
public:
    Canvas(QObject* parent = 0);
    Canvas(std::unique_ptr<GObject> *root, QObject* parent = 0);
    virtual ~Canvas();

    /**
     * @brief Gets the root object of the canvas
     * @return The root GObject
     */
    std::unique_ptr<GObject> const& root();

    /**
     * @brief Get the mouse cursor positon relative to the canvas
     * @return A vertex containing the relative position
     */
    virtual Vertex getCursor() const = 0;

    int executeCommand(Command* command);
    int undoCommand();
    void handleEvent(const Transition &transition);
    virtual void redraw() = 0;
    void addToCurrLayer(std::shared_ptr<GObject> object);
    void changeCurrTool(Tool* newTool);

signals:
    void activeToolChanged(gx::Tool* newTool);

private:
    void initCommon();

private:
    std::unique_ptr<GObject> m_root;
    QVector<Command*> m_commandHistory;
    unsigned int m_currCommand;
    Tool* m_currTool;
    Layer* m_currLayer;
};
}

#endif // CANVAS_H
