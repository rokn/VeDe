#ifndef CANVASWIDGET_H
#define CANVASWIDGET_H

#include <QWidget>
#include "canvas.h"
#include "qtcustompainter.h"

class CanvasWidget : public QWidget
{

    Q_OBJECT
public:
    static CanvasWidget* createCanvasWidget(QWidget *parent = 0, std::shared_ptr<gx::GObject> root = 0);
    void paintEvent(QPaintEvent* event);
    void mouseMoveEvent(QMouseEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void keyPressEvent(QKeyEvent *event);
    void keyReleaseEvent(QKeyEvent *event);

    gx::Canvas *getCanvas() const;
    void setCanvas(gx::Canvas *canvas);

private:
    CanvasWidget(QWidget *parent = 0);
    CanvasWidget(std::shared_ptr<gx::GObject> root, QWidget *parent = 0);

    void initModifierKeys();
    Qt::KeyboardModifier transformToMod(Qt::Key key);
    Qt::Key transformToKey(Qt::KeyboardModifier mod);

private:
    QMap<Qt::KeyboardModifier, bool> m_modifierKeys;

    gx::Canvas* m_canvas;
};

#endif // CANVASWIDGET_H
