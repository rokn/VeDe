#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "tools/linetool.h"
#include "tools/ellipsetool.h"

    // PLACEHOLDER CODE
#include <memory>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    // PLACEHOLDER CODE
    m_canvas = CanvasWidget::createCanvasWidget(ui->canvasFrame);
    ui->canvasFrame->layout()->addWidget(m_canvas);
    ui->canvasFrame->layout()->setMargin(0);
    m_canvas->move(20,20);
    m_canvas->show();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_actionLine_triggered()
{
    m_canvas->changeCurrTool(new gx::LineTool(m_canvas));
}

void MainWindow::on_actionEllipse_triggered()
{
    m_canvas->changeCurrTool(new gx::EllipseTool(m_canvas));
}
