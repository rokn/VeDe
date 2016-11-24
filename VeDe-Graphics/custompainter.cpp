#include "custompainter.h"

void gx::CustomPainter::drawLine(gx::Vertex start, gx::Vertex end)
{
    this->drawLine(start.x(), start.y(), end.x(), end.y());
}

void gx::CustomPainter::drawEllipse(gx::Vertex center, gx::Vertex radius)
{
    this->drawEllipse(center.x(), center.y(), radius.x(), radius.y());
}
