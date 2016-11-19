#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include "graphics/gobject.h"

class CanvasWidget : public QWidget
{
    Q_OBJECT
public:
    explicit CanvasWidget(QWidget *parent = 0);
    void paintEvent(QPaintEvent* event);

signals:

public slots:

private:
    GObject* _root;
};

#endif // CANVASWIDGET_H
