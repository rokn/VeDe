#include "propertyconverter.h"
#include <QDebug>

PropertyConverter::PropertyConverter(gx::Property *prop, QObject *parent)
    :QObject(parent), m_prop(prop)
{
}

void PropertyConverter::onTextChange(const QString &text)
{
    if(m_prop == nullptr)
    {
        qDebug() << "No property to change in converter";
        return;
    }

    switch(m_prop->getType())
    {
        case gx::PROP_INT:
            m_prop->toInt() = text.toInt();
            break;
        case gx::PROP_FLOAT:
            m_prop->toFloat() = text.toFloat();
            break;
        case gx::PROP_STRING:
            m_prop->toString() = text;
            break;
    }
}

void PropertyConverter::onColorChange(const QColor &color)
{
    gx::Color& p_color = m_prop->toColor();

    p_color.setR(color.red());
    p_color.setG(color.green());
    p_color.setB(color.blue());
    p_color.setA(color.alpha());
}
