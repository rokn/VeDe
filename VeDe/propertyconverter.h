#ifndef PROPERTYCONVERTER_H
#define PROPERTYCONVERTER_H

#include "properties/property.h"
#include <QObject>
#include <QColor>

class PropertyConverter : public QObject
{
    Q_OBJECT
public:
    PropertyConverter(gx::Property* prop, QObject *parent = 0);

public slots:
    void onTextChange(const QString& text);
    void onColorChange(const QColor& color);

private:
    gx::Property* m_prop;
};

#endif // PROPERTYCONVERTER_H
