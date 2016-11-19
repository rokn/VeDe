#ifndef CANVAS_H
#define CANVAS_H

#include "graphics/gobject.h"
#include <memory>

namespace gx
{

class Canvas
{
public:
    Canvas();
    Canvas(std::unique_ptr<GObject> root);

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

private:
    std::unique_ptr<GObject> _root;
};
}

#endif // CANVAS_H
