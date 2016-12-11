#include "properywidgetfactory.h"
#include "propertyconverter.h"
#include <QLineEdit>
#include <QIntValidator>
#include <QDoubleValidator>

QWidget *ProperyWidgetFactory::createWidget(gx::Property *prop, QWidget *parent)
{
    QLineEdit* editor;
    PropertyConverter* converter;
    switch(prop->getType())
    {
        case gx::PROP_INT:
            editor = new QLineEdit(QString::number(prop->toInt()), parent);
            editor->setValidator(new QIntValidator(editor));
            converter = new PropertyConverter(prop, editor);
            QObject::connect(editor, SIGNAL(textChanged(QString)), converter, SLOT(onTextChange(QString)));
            return editor;
        case gx::PROP_FLOAT:
            editor = new QLineEdit(QString::number(prop->toFloat()), parent);
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
        //TODO: Implement
//            QLineEdit* editor = new QLineEdit(QString(prop->toInt()), parent);
            return new QLineEdit(parent);
    }
}

QList<QWidget *> ProperyWidgetFactory::createWidgetsForAll(gx::PropertyHolder *propHolder, QWidget *parent)
{
    QList<QWidget*> widgets;

    foreach(auto prop, propHolder->getAllProperties())
    {
        widgets.append(createWidget(prop,parent));
    }

    return widgets;
}
