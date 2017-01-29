#ifndef PROPERTYHOLDER_H
#define PROPERTYHOLDER_H

#include <QMap>
#include <QObject>
#include "properties/property.h"

namespace gx
{
class PropertyHolder
{
//    Q_OBJECT
public:
    PropertyHolder(QObject* parent = 0);
    virtual ~PropertyHolder();
    Property* addProperty(const QString& name, PropertyType propType);
    Property* getProp(const QString& name) const;
    void copyPropertiesFrom(const PropertyHolder& other);
    QList<Property*> getAllProperties();

private:
    QMap<QString, Property*> m_properties;
};
}

#endif // PROPERTYHOLDER_H
