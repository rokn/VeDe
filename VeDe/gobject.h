#ifndef GOBJECT_H
#define GOBJECT_H

#include <QObject>
#include <QPaintEvent>
#include <QPainter>

class GObject : public QObject
{
    Q_OBJECT
public:
    explicit GObject(QObject *parent = 0);
    void paintEvent(QPaintEvent *event, QPaintDevice *device);

signals:

public slots:
};

#endif // GOBJECT_H
