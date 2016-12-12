#include "mainwindow.h"

#include "tools/linetool.h"
#include "tools/ellipsetool.h"
#include "tools/rectangletool.h"
#include "toolaction.h"

#include <QActionGroup>
#include <QGraphicsView>
#include <QLabel>

#include "currtooltoolbar.h"
#include "workspace.h"
#include "properywidgetfactory.h"

    // PLACEHOLDER CODE
#include "properties/propertynames.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setup();
}

MainWindow::~MainWindow()
{
}

void MainWindow::setup()
{
    setupCanvas();
    setupTools();
}

void MainWindow::setupCanvas()
{
    m_canvas = CanvasWidget::createCanvasWidget();
    //TODO: Placeholder
    Workspace* workspace = new Workspace(m_canvas, this);
    setCentralWidget(workspace);
}

void MainWindow::setupTools()
{
    m_toolsBar = new QToolBar(this);
    m_toolsBar->setFloatable(false);
    QActionGroup *group = new QActionGroup(this);
    QList<ToolAction*> actions;
    gx::Tool* ellipse = new gx::EllipseTool(m_canvas->getCanvas());
    ToolAction* ellipseAction = new ToolAction(ellipse, group);
    actions.append(new ToolAction(new gx::LineTool(m_canvas->getCanvas()), group));
    actions.append(ellipseAction);
    actions.append(new ToolAction(new gx::RectangleTool(m_canvas->getCanvas()), group));

    QToolBar* currToolToolBar = new CurrToolToolbar(m_canvas->getCanvas(), this);


    foreach(ToolAction* action, actions)
    {
        action->setCheckable(true);
        m_toolsBar->addAction(action);
    }

    ellipseAction->setChecked(true);
    ellipseAction->trigger();

    this->addToolBar(m_toolsBar);
    this->addToolBar(currToolToolBar);
}
