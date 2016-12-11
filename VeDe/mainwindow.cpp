#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools/linetool.h"
#include "tools/ellipsetool.h"
#include "tools/rectangletool.h"
#include "toolaction.h"
#include <QActionGroup>
#include <QGraphicsView>
#include <QLabel>
#include "workspace.h"
#include "properywidgetfactory.h"

    // PLACEHOLDER CODE
#include "properties/propertynames.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    // PLACEHOLDER CODE
//    m_canvas = CanvasWidget::createCanvasWidget(ui->canvasFrame);
//    ui->canvasFrame->layout()->addWidget(m_canvas);
//    ui->canvasFrame->layout()->setMargin(0);
//    m_canvas->move(20,20);
//    m_canvas->show();
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
    actions.append(new ToolAction(new gx::LineTool(m_canvas->getCanvas()), group));
    actions.append(new ToolAction(ellipse, group));
    actions.append(new ToolAction(new gx::RectangleTool(m_canvas->getCanvas()), group));

    QToolBar* currToolToolBar = new QToolBar(this);

    foreach(auto prop, ellipse->getAllProperties())
    {
        currToolToolBar->addWidget(new QLabel(prop->name(), currToolToolBar));
        currToolToolBar->addWidget(ProperyWidgetFactory::createWidget(prop, currToolToolBar));
    }

    foreach(ToolAction* action, actions)
    {
        action->setCheckable(true);
        m_toolsBar->addAction(action);
    }

    this->addToolBar(m_toolsBar);
    this->addToolBar(currToolToolBar);
}
