#include "propertywidgetfactory.h"
#include "propertyconverter.h"
#include "converters.h"
#include "colorchangebutton.h"
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>

QWidget *PropertyWidgetFactory::createWidget(gx::Property *prop, QWidget *parent)
{
    QLineEdit* editor;
    ColorChangeButton* colorButton;
    PropertyConverter* converter;
    switch(prop->getType())
    {
        case gx::PROP_INT:
            editor = new QLineEdit(QString::number(prop->toInt()), parent);
            editor->setValidator(new QIntValidator(editor));
            converter = new PropertyConverter(prop, editor);
            QObject::connect(editor, SIGNAL(textChanged(QString)), converter, SLOT(onTextChange(QString)));
            return editor;
        case gx::PROP_DOUBLE:
            editor = new QLineEdit(QString::number(prop->toDouble()), parent);
            editor->setValidator(new QDoubleValidator(editor));
            converter = new PropertyConverter(prop, editor);
            QObject::connect(editor, SIGNAL(textChanged(QString)), converter, SLOT(onTextChange(QString)));
            return editor;
        case gx::PROP_STRING:
            editor = new QLineEdit(prop->toString(), parent);
            converter = new PropertyConverter(prop, editor);
            QObject::connect(editor, SIGNAL(textChanged(QString)), converter, SLOT(onTextChange(QString)));
            return editor;
        case gx::PROP_COLOR:
//            QLineEdit* editor = new QLineEdit(QString(prop->toInt()), parent);
            colorButton = new ColorChangeButton(gx::Converters::toQColor(prop->toColor()), parent);
            converter = new PropertyConverter(prop, colorButton);
            QObject::connect(colorButton, SIGNAL(colorChanged(QColor)), converter, SLOT(onColorChange(QColor)));
            return colorButton;

        default: return nullptr;
    }
}

QList<QWidget *> PropertyWidgetFactory::createWidgetsForAll(gx::PropertyHolder *propHolder, QWidget *parent)
{
    QList<QWidget*> widgets;

    foreach(auto prop, propHolder->getAllProperties())
    {
        widgets.append(createWidget(prop,parent));
    }

    return widgets;
}
