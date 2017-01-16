#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvasimpl.h"

QT_BEGIN_NAMESPACE
class QToolBar;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void onUndo(bool checked = false);
    void onRedo(bool checked = false);

private:
    void setup();
    void setupCanvas();
    void setupTools();

private:
    CanvasImpl *m_canvas;
    QToolBar* m_toolsBar;
};

#endif // MAINWINDOW_H
