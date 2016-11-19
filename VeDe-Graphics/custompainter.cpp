#include "custompainter.h"

void gx::CustomPainter::drawLine(gx::Vertex start, gx::Vertex end)
{
    this->drawLine(start.x(), start.y(), end.x(), end.y());
}
