#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvaswidget.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_actionLine_triggered();

    void on_actionEllipse_triggered();

    void on_actionRectangle_triggered();

private:
    Ui::MainWindow *ui;
    CanvasWidget *m_canvas;
};

#endif // MAINWINDOW_H
