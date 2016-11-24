#include "mainwindow.h"
#include "ui_mainwindow.h"

    // PLACEHOLDER CODE
#include <memory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // PLACEHOLDER CODE
    CanvasWidget *canvas = CanvasWidget::createCanvasWidget(ui->mainFrame);
    ui->mainFrame->layout()->addWidget(canvas);
    ui->mainFrame->layout()->setMargin(0);
    canvas->move(20,20);
    canvas->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
