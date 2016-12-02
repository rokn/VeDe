#include "qtcustompainter.h"
#include <QRgb>

QtCustomPainter::QtCustomPainter(QPaintDevice* canvas)
    :m_painter(canvas)
{
}

void QtCustomPainter::drawLine(float x1, float y1, float x2, float y2)
{
    m_painter.drawLine(x1, y1, x2, y2);
}

void QtCustomPainter::drawEllipse(float cX, float cY, float rX, float rY)
{
    m_painter.drawEllipse(QPointF(cX, cY), rX, rY);
}

void QtCustomPainter::drawRectangle(float upLeftX, float upLeftY, float downRightX, float downRightY)
{
    m_painter.drawRect(upLeftX, upLeftY, downRightX - upLeftX, downRightY - upLeftY);
}

void QtCustomPainter::setStrokeWidth(float width)
{
    m_pen.setWidth((int)width);
    onChangePen();
}

void QtCustomPainter::setStrokeColor(gx::Color color)
{
    m_pen.setColor(toQColor(color));
    onChangePen();
}

QColor QtCustomPainter::toQColor(gx::Color c)
{
    return QColor(c.r(), c.g(), c.b(), c.a());
}

void QtCustomPainter::onChangePen()
{
    m_painter.setPen(m_pen);
}
