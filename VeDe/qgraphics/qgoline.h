#ifndef QGOLINE_H
#define QGOLINE_H

#include "graphics/line.h"

class QGOLine : public Line
{
public:
    QGOLine();
    QGOLine(Vertex start, Vertex end);

protected:
    void drawSelf(QPaintEvent *event, QPaintDevice *device);
};

#endif // QGOLINE_H
