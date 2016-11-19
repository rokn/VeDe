#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <memory>
#include "graphics/line.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    gx::Vertex start(0.0f,0.0f);
    gx::Vertex end(100.0f,100.0f);
    std::unique_ptr<gx::GObject> line(new gx::Line(start, end));
    CanvasWidget *canvas = new CanvasWidget(line, ui->mainFrame);
    canvas->move(20,20);
    canvas->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
