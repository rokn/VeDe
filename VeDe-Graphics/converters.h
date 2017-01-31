#ifndef CONVERTERS_H
#define CONVERTERS_H


#include "color.h"
#include <QColor>
#include "vertex.h"
#include <QPointF>

namespace gx
{
namespace Converters
{
    QColor toQColor(const gx::Color &c);
    gx::Color toGxColor(const QColor &c);
    QPointF toPoint(const gx::Vertex &v);
    gx::Vertex toVertex(const QPointF &p);
}
}

#endif // CONVERTERS_H
