#ifndef PROPERYWIDGETFACTORY_H
#define PROPERYWIDGETFACTORY_H

#include <QWidget>
#include <QList>
#include "properties/property.h"
#include "properties/propertyholder.h"

class PropertyWidgetFactory
{
public:
    static QWidget* createWidget(gx::Property* prop, QWidget *parent = 0);
    static QList<QWidget*> createWidgetsForAll(gx::PropertyHolder* propHolder, QWidget* parent = 0);
};

#endif // PROPERYWIDGETFACTORY_H
