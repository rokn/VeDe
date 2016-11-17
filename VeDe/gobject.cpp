#include "gobject.h"

GObject::GObject(QObject *parent) : QObject(parent)
{

}

void GObject::paintEvent(QPaintEvent *event, QPaintDevice *device)
{
    QPainter painter(device);
    painter.drawLine(0,0,100,100);
}
