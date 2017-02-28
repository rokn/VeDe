#include "mainwindow.h"

#include "tools/linetool.h"
#include "tools/ellipsetool.h"
#include "tools/rectangletool.h"
#include "tools/pathtool.h"
#include "tools/manipulatetool.h"
#include "toolaction.h"

#include <QActionGroup>
#include <QGraphicsView>
#include <QLabel>
#include <QMenuBar>
#include <QMessageBox>
#include <QApplication>
#include <QInputDialog>
#include <QFileDialog>
#include <QDir>

#include "currtooltoolbar.h"

#include "canvasmanagersvg.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent)
{
    setup();
}

MainWindow::~MainWindow()
{
    if(m_currFileName != nullptr) {
        delete m_currFileName;
    }
}

void MainWindow::onUndo()
{
    m_canvas->undoCommand();
}

void MainWindow::onRedo()
{
    m_canvas->redoCommand();
}

void MainWindow::newFile()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                  "Creating new canvas",
                  "All unsaved changes will be lost.",
                  QMessageBox::Ok|QMessageBox::Cancel);

    if (reply != QMessageBox::Ok) {
        return;
    }

    bool ok;

    double width = QInputDialog::getDouble(this, "Create new canvas", "Width of the canvas", 0, 0, 10000, 1, &ok);
    if (!ok) return;

    double height = QInputDialog::getDouble(this, "Create new canvas", "Height of the canvas", 0, 0, 10000, 1, &ok);
    if (!ok) return;

    gx::Tool* currTool = nullptr;

    if(m_canvas != nullptr) {
        currTool = m_canvas->getCurrTool();
        delete m_canvas;
    }

    delete m_toolsBar;
    delete m_currToolToolbar;
    m_currFileName = nullptr;


    m_canvas = CanvasImpl::createCanvas(this, width, height);
    m_canvas->changeCurrTool(currTool);
    m_workspace->setCanvas(m_canvas);
    setupTools();
}

void MainWindow::openFile()
{

}

void MainWindow::save()
{
    if(m_currFileName == nullptr) {
        saveAs();
    } else {
        gx::CanvasManagerSVG manager;
        manager.saveCanvas(m_currFileName->toStdString(), m_canvas);
    }
}

void MainWindow::saveAs()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                 tr("Save File"),
                                 QDir::currentPath(),
                                 "SVG (*.svg)");
    if(!filename.endsWith(".svg")) {
        filename.append(".svg");
    }
    gx::CanvasManagerSVG manager;
    if(manager.saveCanvas(filename.toStdString(), m_canvas)) {
        m_currFileName = new QString(filename);
    }
}

void MainWindow::exit()
{
    QMessageBox::StandardButton reply;
    reply = QMessageBox::question(this,
                  "Exitting...",
                  "Do you really want to exit VeDe? All unsaved changes will be lost.",
                  QMessageBox::Yes|QMessageBox::No);

    if (reply == QMessageBox::Yes) {
        QApplication::quit();
    }
}

void MainWindow::setup()
{
    m_currFileName = nullptr;
    setupCanvas();
    setupTools();
    setupActions();
    setupMenus();
}

void MainWindow::setupCanvas()
{
    m_canvas = CanvasImpl::createCanvas(this, 800, 600);
    m_workspace = new Workspace(m_canvas, this);
    setCentralWidget(m_workspace);
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
    actions.append(new ToolAction(new gx::ManipulateTool(m_canvas), group));

    foreach(ToolAction* action, actions)
    {
        action->setCheckable(true);
        m_toolsBar->addAction(action);
    }

    this->addToolBar(m_toolsBar);

    m_currToolToolbar = new CurrToolToolbar(m_canvas, this);
    this->addToolBar(m_currToolToolbar);

    ellipseAction->setChecked(true);
    ellipseAction->trigger();
}

void MainWindow::setupActions()
{
    m_undoAction = new QAction(tr("&Undo"), this);
    m_undoAction->setShortcut(QKeySequence(QKeySequence::Undo));
    connect(m_undoAction, SIGNAL(triggered()), this, SLOT(onUndo()));

    m_redoAction = new QAction(tr("&Redo"), this);
    m_redoAction->setShortcut(QKeySequence(QKeySequence::Redo));
    connect(m_redoAction, SIGNAL(triggered()), this, SLOT(onRedo()));

    m_newAction = new QAction(tr("&New"), this);
    m_newAction->setShortcut(QKeySequence(QKeySequence::New));
    connect(m_newAction, SIGNAL(triggered()), this, SLOT(newFile()));

    m_openAction = new QAction(tr("&Open"), this);
    m_openAction->setShortcut(QKeySequence(QKeySequence::Open));
    connect(m_openAction, SIGNAL(triggered()), this, SLOT(openFile()));

    m_saveAction = new QAction(tr("&Save"), this);
    m_saveAction->setShortcut(QKeySequence(QKeySequence::Save));
    connect(m_saveAction, SIGNAL(triggered()), this, SLOT(save()));

    m_saveAsAction = new QAction(tr("Save As"), this);
    m_saveAsAction->setShortcut(QKeySequence(QKeySequence::SaveAs));
    connect(m_saveAsAction, SIGNAL(triggered()), this, SLOT(saveAs()));

    m_exitAction = new QAction(tr("&Exit"), this);
    m_exitAction->setShortcut(QKeySequence(QKeySequence::Quit));
    connect(m_exitAction, SIGNAL(triggered()), this, SLOT(exit()));
}

void MainWindow::setupMenus()
{
    auto fileMenu =  menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(m_newAction);
    fileMenu->addAction(m_saveAction);
    fileMenu->addAction(m_saveAsAction);
    fileMenu->addSeparator();
    fileMenu->addAction(m_exitAction);

    auto editMenu =  menuBar()->addMenu(tr("&Edit"));
    editMenu->addAction(m_undoAction);
    editMenu->addAction(m_redoAction);
}
