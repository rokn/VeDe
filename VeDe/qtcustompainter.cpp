#include "qtcustompainter.h"

QtCustomPainter::QtCustomPainter(QPaintDevice* canvas)
    :_painter(canvas)
{
}

void QtCustomPainter::drawLine(int x1, int y1, int x2, int y2)
{
    _painter.drawLine(x1, y1, x2, y2);
}
