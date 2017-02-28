#ifndef CANVASMANAGERSVG_H
#define CANVASMANAGERSVG_H

#include "canvasmanager.h"
#include "layer.h"
#include "objects/ellipse.h"
#include "objects/line.h"
#include "objects/path.h"
#include "objects/rectangle.h"
#include <sstream>
#include <QTransform>
#include <string>

namespace gx
{
class CanvasManagerSVG : public CanvasManager
{
public:
    bool saveCanvas(std::string filename, const Canvas* canvas);
    Canvas* loadCanvas(std::string filename);

private:
    std::string elemEnd(std::string elem);

    template <typename T>
    std::string attribute(std::string const & attribute_name,
        T const & value, std::string const & unit = "")
    {
        std::stringstream ss;
        ss << attribute_name << "=\"" << value << unit << "\" ";
        return ss.str();
    }

    void drawObject(SharedGObject layer, std::stringstream& ss, int depth = 0);
    void drawLine(const gx::Line* line, std::stringstream& ss);
    void drawEllipse(const gx::Ellipse* ellipse, std::stringstream& ss);
    void drawRectangle(const gx::Rectangle* rectangle, std::stringstream& ss);
    void drawPath(const gx::Path* path, std::stringstream& ss);
    std::string shapeAttributes(const PropertyHolder *object);
    std::string colorToSvg(const Color &color);
    std::string toSvg(const QTransform& transform);
    std::string toSvg(const Vertex& vertex);
};
}

#endif // CANVASMANAGERSVG_H
