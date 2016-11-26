#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include "canvas.h"
#include "qtcustompainter.h"

class CanvasWidget : public QWidget, public gx::Canvas
{
    Q_OBJECT
public:
    static CanvasWidget* createCanvasWidget(QWidget *parent = 0, std::unique_ptr<gx::GObject> *root = 0);
    void paintEvent(QPaintEvent* event);
    void redraw();

    gx::Vertex getCursor() const;
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
signals:

public slots:

private:
    CanvasWidget(QWidget *parent = 0);
    CanvasWidget(std::unique_ptr<gx::GObject> *root, QWidget *parent = 0);
};

#endif // CANVASWIDGET_H
