#ifndef PROPERTYCONVERTER_H
#define PROPERTYCONVERTER_H

#include "properties/property.h"
#include <QObject>

class PropertyConverter : QObject
{
    Q_OBJECT
public:
    PropertyConverter(gx::Property* prop);

public slots:

private:
    gx::Property* m_prop;
};

#endif // PROPERTYCONVERTER_H
