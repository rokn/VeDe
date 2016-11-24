#include "mainwindow.h"
#include "ui_mainwindow.h"



    // PLACEHOLDER CODE
#include <memory>
#include "line.h"
#include "commands/addlinecommand.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // PLACEHOLDER CODE
    gx::Vertex start(0.0f,0.0f);
    gx::Vertex end(100.0f,100.0f);
    gx::Vertex start2(100.0f,100.0f);
    gx::Vertex end2(150.0f,100.0f);
    std::shared_ptr<gx::Line> line2(new gx::Line(start2,end2));
    std::unique_ptr<gx::GObject> line(new gx::Line(start, end));
    CanvasWidget *canvas = new CanvasWidget(line, ui->mainFrame);
    ui->mainFrame->layout()->addWidget(canvas);
    canvas->move(20,20);
    canvas->show();
    //TODO: Make AddLineCommand -> AddGobjectCommand
    gx::Command* command = new gx::AddLineCommand(line2, static_cast<gx::Canvas*>(canvas));
    canvas->executeCommand(command);
}

MainWindow::~MainWindow()
{
    delete ui;
}
