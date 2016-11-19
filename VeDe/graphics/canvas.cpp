#include "canvas.h"

gx::Canvas::Canvas()
{

}

gx::Canvas::Canvas(std::unique_ptr<gx::GObject> root)
{
    _root = std::move(root);
}

std::unique_ptr<gx::GObject> const& gx::Canvas::root() const
{
    return _root;
}
