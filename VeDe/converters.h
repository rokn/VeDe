#ifndef CONVERTERS_H
#define CONVERTERS_H

#include "color.h"
#include <QColor>

namespace Converters
{
    QColor toQColor(const gx::Color &c);
    gx::Color toGxColor(const QColor &c);
}

#endif // CONVERTERS_H
