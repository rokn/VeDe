#include "canvasmanagersvg.h"


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
}

gx::Canvas *gx::CanvasManagerSVG::loadCanvas(std::string filename)
{

}

std::string gx::CanvasManagerSVG::elemEnd(std::string elem)
{
    std::string elemStr = "</" + elem + ">";
    return elemStr;
}
