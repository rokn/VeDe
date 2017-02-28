#include "canvasmanagersvg.h"
#include "gobjecttypes.h"
#include "properties/propertynames.h"
#include <fstream>


bool gx::CanvasManagerSVG::saveCanvas(std::string filename, const gx::Canvas *canvas)
{
    std::stringstream ss;
    ss << "<?xml " << attribute("version", "1.0") << attribute("standalone", "no")
        << "?>\n<!DOCTYPE svg PUBLIC \"-//W3C//DTD SVG 1.1//EN\" "
        << "\"http://www.w3.org/Graphics/SVG/1.1/DTD/svg11.dtd\">\n<svg "
        << attribute("width", canvas->getWidth(), "px")
        << attribute("height", canvas->getHeight(), "px")
        << attribute("xmlns", "http://www.w3.org/2000/svg")
        << attribute("version", "1.1") << ">\n";

    drawObject(canvas->root(), ss);

    ss << elemEnd("svg");

    std::ofstream ofs(filename.c_str());
    if (!ofs.good())
        return false;

    ofs << ss.str();
    ofs.close();
    return true;
}

gx::Canvas *gx::CanvasManagerSVG::loadCanvas(std::string filename)
{
}

std::string gx::CanvasManagerSVG::elemEnd(std::string elem)
{
    std::string elemStr = "</" + elem + ">";
    return elemStr;
}

void gx::CanvasManagerSVG::drawLine(const gx::Line *line, std::stringstream &ss)
{
    ss << "<line "
       << toSvg(line->getTransform())
       << attribute("x1", line->start().x())
       << attribute("y1", line->start().y())
       << attribute("x2", line->end().x())
       << attribute("y2", line->end().y())
       << shapeAttributes(line) << "/>";
}

void gx::CanvasManagerSVG::drawEllipse(const gx::Ellipse *ellipse, std::stringstream &ss)
{
    ss << "<ellipse "
       << toSvg(ellipse->getTransform())
       << attribute("cx", ellipse->center().x())
       << attribute("cy", ellipse->center().y())
       << attribute("rx", ellipse->radius().x())
       << attribute("ry", ellipse->radius().y())
       << shapeAttributes(ellipse) << "/>";
}

void gx::CanvasManagerSVG::drawRectangle(const gx::Rectangle *rectangle, std::stringstream &ss)
{
    Vertex tl = rectangle->getTopLeft();
    Vertex br = rectangle->getBottomRight();
    ss << "<rect "
       << toSvg(rectangle->getTransform())
       << attribute("x", tl.x())
       << attribute("y", tl.y())
       << attribute("width", br.x() - tl.x())
       << attribute("height", br.y() - tl.y())
       << shapeAttributes(rectangle) << "/>";
}

void gx::CanvasManagerSVG::drawPath(const gx::Path *path, std::stringstream &ss)
{
    Vertex curr, prev, control1, control2;
    bool hasControl1 = path->controls()[0], hasControl2 = false;
    int vIndex = (hasControl1) ? 2 : 1;
    control1 = path->vertices()[vIndex - 1];

    ss << "<path "
       << toSvg(path->getTransform())
       << shapeAttributes(path)
       << "d=\"M" << toSvg(path->vertices()[0]);

    prev = path->vertices()[0];


    for (auto control = path->controls().begin() + 1; control != path->controls().end(); ++control) {
        curr = path->vertices()[vIndex];
        hasControl2 = *control;
        if(hasControl2) {
            control2 = curr * 2.0 - path->vertices()[vIndex+1];
        } else {
            control2 = curr;
        }

        if(hasControl1 || hasControl2){
            ss << "C" << toSvg(control1) << toSvg(control2) << toSvg(curr);
        } else {
            ss << "L" << toSvg(curr);
        }

        hasControl1 = hasControl2;
        control1 = control2;
        prev = curr;

        if(hasControl2) {
            vIndex += 2;
            control1 = curr * 2.0 - control1;
        } else {
            vIndex ++;
        }
    }

    if(path->isClosed()) {
        if(hasControl1) {
            ss << "C" << toSvg(control1) << toSvg(path->vertices()[0]) << toSvg(path->vertices()[0]);
        }
        ss <<"Z";
    }
    ss <<"\"/>";
}

std::string gx::CanvasManagerSVG::shapeAttributes(const gx::PropertyHolder* object)
{
    std::stringstream ss;
    ss << "style=\"stroke:"<< colorToSvg(object->getProp(PROP::STROKE_COLOR)->toColor())
       << ";stroke-width:" << object->getProp(PROP::STROKE_WIDTH)->toDouble()
       << ";fill:" << colorToSvg(object->getProp(PROP::BACK_COLOR)->toColor()) << "\" ";
    return ss.str();
}

std::string gx::CanvasManagerSVG::colorToSvg(const gx::Color& color)
{
    std::stringstream ss;
    ss << "rgba(" << color.r() << ','
       << color.g() << ','
       << color.b() << ','
       << color.a() << ')';
    return ss.str();
}

std::string gx::CanvasManagerSVG::toSvg(const QTransform &transform)
{
    std::stringstream ss;
    ss << "transform=\"matrix("
       << transform.m11() << ','
       << transform.m12() << ','
       << transform.m21() << ','
       << transform.m22() << ','
       << transform.m31() << ','
       << transform.m32() << ")\" ";
    return ss.str();
}

std::string gx::CanvasManagerSVG::toSvg(const gx::Vertex &vertex)
{
    std::stringstream ss;
    ss << vertex.x() << " " << vertex.y() << " ";
    return ss.str();
}

void gx::CanvasManagerSVG::drawObject(const SharedGObject object, std::stringstream& ss, int depth)
{
    for (int i = 0; i < depth; ++i) {
        ss << "  ";
    }

    GObjectTypes::GObjectType type = GObjectTypes::getObjectType(object);
    switch(type){
        case GObjectTypes::Ellipse:
            drawEllipse(static_cast<const Ellipse*>(object.get()), ss);
            break;
        case GObjectTypes::Line:
            drawLine(static_cast<const Line*>(object.get()), ss);
            break;
        case GObjectTypes::Rectangle:
            drawRectangle(static_cast<const Rectangle*>(object.get()), ss);
            break;
        case GObjectTypes::Path:
            drawPath(static_cast<const Path*>(object.get()), ss);
            break;
        case GObjectTypes::Layer:
            ss << "<g>";
            depth++;
            break;
    }
    ss << std::endl;

    foreach (auto obj, object->getChildren()) {
        drawObject(obj, ss, depth);
    }

    if(type == GObjectTypes::Layer) {
        for (int i = 0; i < depth - 1; ++i) {
            ss << "  ";
        }
        ss << elemEnd("g") << std::endl;
    }
}
