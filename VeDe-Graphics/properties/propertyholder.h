#ifndef PROPERTYHOLDER_H
#define PROPERTYHOLDER_H

#include <QMap>
#include "properties/property.h"

namespace gx
{
class PropertyHolder
{
public:
    virtual ~PropertyHolder();
    Property* addProperty(const QString& name, PropertyType propType);
    Property* getProp(const QString& name) const;
    void copyPropertiesFrom(const PropertyHolder& other);

private:
    QMap<QString, Property*> m_properties;
};
}

#endif // PROPERTYHOLDER_H
