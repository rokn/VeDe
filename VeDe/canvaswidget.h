#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include "graphics/canvas.h"
#include "qtcustompainter.h"

class CanvasWidget : public QWidget, public gx::Canvas
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent* event);

    gx::Vertex getCursor() const;
signals:

public slots:

};

#endif // CANVASWIDGET_H
