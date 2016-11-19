#ifndef QTCUSTOMPAINTER_H
#define QTCUSTOMPAINTER_H

#include "graphics/custompainter.h"
#include <QPaintDevice>
#include <QPainter>

class QtCustomPainter : public gx::CustomPainter
{
public:
    QtCustomPainter(QPaintDevice* canvas);
    void drawLine(int x1, int y1, int x2, int y2);

private:
    QPainter _painter;
};

#endif // QTCUSTOMPAINTER_H
