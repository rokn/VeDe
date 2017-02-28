#ifndef CANVASMANAGERSVG_H
#define CANVASMANAGERSVG_H

#include "canvasmanager.h"
#include <sstream>
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


};
}

#endif // CANVASMANAGERSVG_H
