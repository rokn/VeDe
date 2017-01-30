#ifndef PROPERTYHOLDER_H
#define PROPERTYHOLDER_H

#include <QMap>
#include <QObject>
#include "properties/property.h"

namespace gx
{
class PropertyHolder
{
    typedef std::function<void(PropertyHolder*, const QString&)> GobjectCallback;
public:
    PropertyHolder(QObject* parent = 0);
    virtual ~PropertyHolder();
    Property* addProperty(const QString& name, PropertyType propType);
    Property* getProp(const QString& name) const;
    void copyPropertiesFrom(const PropertyHolder& other);
    QList<Property*> getAllProperties();
    virtual void preparePropertyChange();
    virtual void updateProperties();

private:
    QMap<QString, Property*> m_properties;
    QList<GobjectCallback> m_onChangeCallbacks;
};
}

#endif // PROPERTYHOLDER_H
