#include "propertyholder.h"

gx::PropertyHolder::PropertyHolder()
{

}

gx::PropertyHolder::~PropertyHolder()
{
    foreach (auto& key, m_properties.keys()) {
        delete m_properties.value(key);
    }
}

gx::Property *gx::PropertyHolder::addProperty(const QString &name, gx::PropertyType propType)
{
    Property* prop = Property::createProperty(name, propType);
    m_properties.insert(name, prop);
    return prop;
}

gx::Property *gx::PropertyHolder::getProp(const QString &name) const
{
    auto itr = m_properties.find(name);

    if(itr != m_properties.end())
    {
        return itr.value();
    }
    return Q_NULLPTR;
}

void gx::PropertyHolder::copyPropertiesFrom(const gx::PropertyHolder &other)
{
    foreach (auto& key, other.m_properties.keys()) {
        this->m_properties.insert(key, new Property(*other.m_properties.value(key)));
    }
}

QList<gx::Property *> gx::PropertyHolder::getAllProperties()
{
    return m_properties.values();
}

void gx::PropertyHolder::preparePropertyChange()
{
}

void gx::PropertyHolder::updateProperties()
{
}
