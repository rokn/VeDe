#include "currtooltoolbar.h"
#include "propertywidgetfactory.h"

CurrToolToolbar::CurrToolToolbar(gx::Canvas *canvas, QWidget *parent)
    :QToolBar(parent)
{
//    connect(canvas, SIGNAL(activeToolChanged(gx::Tool*)), this, SLOT(canvasToolChanged(gx::Tool*)));
    canvas->onToolChanged() += [this](gx::Tool* t){
        canvasToolChanged(t);
    };

    m_nameLabel = new QLabel(this);
    setAllowedAreas(Qt::TopToolBarArea | Qt::BottomToolBarArea);
    setFloatable(false);

    auto widgetList = PropertyWidgetFactory::createWidgetsForAll(canvas, this);

    foreach(auto widget, widgetList)
    {
        addWidget(widget);
    }
}

void CurrToolToolbar::canvasToolChanged(gx::Tool *newTool)
{
    foreach(auto widget, m_propertyWidgets)
    {
        delete widget;
    }

    m_propertyWidgets.clear();

    foreach(auto prop, newTool->getAllProperties())
    {
        QWidget* label = new QLabel(prop->name(), this);
        QWidget* editor = PropertyWidgetFactory::createWidget(prop, this);
        addWidget(label);
        addWidget(editor);
        m_propertyWidgets.append(label);
        m_propertyWidgets.append(editor);
    }
}
