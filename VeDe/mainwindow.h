#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "canvasimpl.h"
#include "workspace.h"

QT_BEGIN_NAMESPACE
class QToolBar;
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void onUndo();
    void onRedo();
    void newFile();
    void openFile();
    void save();
    void saveAs();
    void exit();

private:
    void setup();
    void setupCanvas();
    void setupTools();
    void setupActions();
    void setupMenus();

private:
    CanvasImpl *m_canvas;
    Workspace *m_workspace;
    QToolBar* m_toolsBar;
    QToolBar* m_currToolToolbar;
    QString* m_currFileName;
//    QList<Tool*> m_tools;

    QAction* m_newAction;
    QAction* m_openAction;
    QAction* m_saveAction;
    QAction* m_saveAsAction;
    QAction* m_exitAction;
    QAction* m_undoAction;
    QAction* m_redoAction;

};

#endif // MAINWINDOW_H
