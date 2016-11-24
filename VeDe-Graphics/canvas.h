#ifndef CANVAS_H
#define CANVAS_H

#include "gobject.h"
#include "layer.h"
#include "commands/command.h"
#include <memory>
#include <QVector>

namespace gx
{

class Canvas
{
public:
    Canvas();
    Canvas(std::unique_ptr<GObject>& root);
    virtual ~Canvas();

    /**
     * @brief Gets the root object of the canvas
     * @return The root GObject
     */
    std::unique_ptr<GObject> const& root() const;

    /**
     * @brief Get the mouse cursor positon relative to the canvas
     * @return A vertex containing the relative position
     */
    virtual Vertex getCursor() const = 0;

    int executeCommand(Command* command);
    int undoCommand();

private:
    std::unique_ptr<GObject> m_root;
    QVector<Command*> m_commandHistory;
    unsigned int m_currCommand;
};
}

#endif // CANVAS_H
