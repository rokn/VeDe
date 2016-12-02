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
    static Property* createProperty(const QString &name, PropertyType type);
    ~Property();

    void resetToDefault();
    const int& toInt() const;
    const float& toFloat() const;
    const QString& toString() const;
    const Color& toColor() const;
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
