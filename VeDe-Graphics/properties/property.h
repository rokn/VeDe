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
    PROP_DOUBLE,
    PROP_STRING,
    PROP_COLOR,
};

class Property
{
public:
    static Property* createProperty(const QString &name, PropertyType type);
    Property(const Property& other);
    ~Property();

    void resetToDefault();
    const int& toInt() const;
    const double& toDouble() const;
    const QString& toString() const;
    const Color& toColor() const;
    int& toInt();
    double& toDouble();
    QString& toString();
    Color& toColor();
    void setInt(int value);
    void setDouble(double value);
    void setString(const QString &value);
    void setColor(const Color& value);
//    void get s

    QString name() const;
    void setName(const QString &name);

    PropertyType getType() const;

private:
    Property(PropertyType type, QString name);

    union PropertyValue
    {
        int i;
        double d;
        QString* s;
        Color* c;
    }m_value;

    PropertyType m_type;
    QString m_name;
};
}

#endif // PROPERTY_H
