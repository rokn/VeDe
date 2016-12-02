#ifndef PROPERTY_H
#define PROPERTY_H

#include <memory>
#include <QString>
#include "color.h"
#include "graphics_exceptions.h"

namespace gx
{

enum PropertyType
{
    PROP_INT,
    PROP_FLOAT,
    PROP_STRING,
    PROP_COLOR,
};

class Property
{
public:
    Property* createProperty(PropertyType type, QString name);
    ~Property();

    void resetToDefault();
    int& toInt();
    float& toFloat();
    QString& toString();
    Color& toColor();
//    void get s

    QString name() const;
    void setName(const QString &name);

private:
    Property(PropertyType type, QString name);

    union PropertyValue
    {
        int i;
        float f;
        QString* s;
        Color* c;
    }m_value;

    PropertyType m_type;
    QString m_name;
};
}

#endif // PROPERTY_H
