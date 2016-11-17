#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    CanvasWidget *canvas = new CanvasWidget(ui->mainFrame);
    canvas->move(20,20);
    canvas->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
