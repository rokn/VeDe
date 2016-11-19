#include "colorproperty.h"

ColorProperty::ColorProperty(Color color)
    :_color(color)
{

}

const QColor& ColorProperty::getColor() const
{
    return _color;
}

void ColorProperty::resetToDefault()
{
    _color = QColor::fromRgb(255, 255, 255);
}

void ColorProperty::copyFromProperty(const Property *prop)
{
    const ColorProperty* clr = dynamic_cast<const ColorProperty*>(prop);

    if(clr != Q_NULLPTR)
    {
        _color = clr->_color;
    }
    else
    {
        //TODO: handle error, possibly throw
    }
}

std::shared_ptr<Property> ColorProperty::clone() const
{
    return std::make_shared<ColorProperty>(ColorProperty(_color));

}

void ColorProperty::setColor(const QColor &color)
{
    _color = color;
}

ColorProperty::operator QColor() const
{
    return QColor(_color);
}
