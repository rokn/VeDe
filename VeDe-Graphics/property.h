#ifndef PROPERTY_H
#define PROPERTY_H

#include <memory>

class Property
{
public:
    Property();

    virtual void resetToDefault() = 0;
    virtual void copyFromProperty(const Property* prop) = 0;
    virtual std::shared_ptr<Property> clone() const = 0;
};

#endif // PROPERTY_H
