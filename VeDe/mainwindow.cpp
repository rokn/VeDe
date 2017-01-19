#include "mainwindow.h"

#include "tools/linetool.h"
#include "tools/ellipsetool.h"
#include "tools/rectangletool.h"
#include "tools/pathtool.h"
#include "toolaction.h"

#include <QActionGroup>
#include <QGraphicsView>
#include <QLabel>

#include "currtooltoolbar.h"
#include "workspace.h"
#include "propertywidgetfactory.h"

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

void MainWindow::onUndo(bool checked)
{
    m_canvas->undoCommand();
}

void MainWindow::onRedo(bool checked)
{
    m_canvas->redoCommand();
}

void MainWindow::setup()
{
    setupCanvas();
    setupTools();
}

void MainWindow::setupCanvas()
{
    m_canvas = CanvasImpl::createCanvas();
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
    gx::Tool* ellipse = new gx::EllipseTool(m_canvas);
    ToolAction* ellipseAction = new ToolAction(ellipse, group);
    actions.append(new ToolAction(new gx::LineTool(m_canvas), group));
    actions.append(ellipseAction);
    actions.append(new ToolAction(new gx::RectangleTool(m_canvas), group));
    actions.append(new ToolAction(new gx::PathTool(m_canvas), group));

    QToolBar* currToolToolBar = new CurrToolToolbar(m_canvas, this);

    QAction *undoAction = new QAction("Undo", this);
    undoAction->setShortcut(QKeySequence(QKeySequence::Undo));
    connect(undoAction, SIGNAL(triggered(bool)), this, SLOT(onUndo(bool)));
    this->addAction(undoAction);

    QAction *redoAction = new QAction("Redo", this);
    redoAction->setShortcut(QKeySequence(QKeySequence::Redo));
    connect(redoAction, SIGNAL(triggered(bool)), this, SLOT(onRedo(bool)));
    this->addAction(redoAction);


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
