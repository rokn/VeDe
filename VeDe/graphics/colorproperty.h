#ifndef COLORPROPERTY_H
#define COLORPROPERTY_H

#include <QColor>
#include "graphics/property.h"

class ColorProperty : public Property
{
public:
    ColorProperty(QColor color);
    const QColor& getColor() const;
    void setColor(const QColor &color);
    void resetToDefault();
    void copyFromProperty(const Property* prop);
    std::shared_ptr<Property> clone() const;
    operator QColor() const;


private:
    QColor _color;
};

#endif // COLORPROPERTY_H
