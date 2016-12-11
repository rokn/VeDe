#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvaswidget.h"

QT_BEGIN_NAMESPACE
class QToolBar;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void setup();
    void setupCanvas();
    void setupTools();

private:
    CanvasWidget *m_canvas;
    QToolBar* m_toolsBar;
};

#endif // MAINWINDOW_H
