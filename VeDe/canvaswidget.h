#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include "canvas.h"
#include "qtcustompainter.h"

class CanvasWidget : public QWidget, public gx::Canvas
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = 0);
    explicit CanvasWidget(std::unique_ptr<gx::GObject>& root, QWidget *parent = 0);
    void paintEvent(QPaintEvent* event);

    gx::Vertex getCursor() const;
signals:

public slots:

};

#endif // CANVASWIDGET_H
