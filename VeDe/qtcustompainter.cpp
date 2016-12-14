#include "qtcustompainter.h"
#include <QRgb>

QtCustomPainter::QtCustomPainter(QPaintDevice* canvas)
    :m_painter(canvas)
{
    m_pen.setJoinStyle(Qt::MiterJoin);
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
    m_painter.drawRect((int)upLeftX, (int)upLeftY, (int)downRightX - (int)upLeftX, (int)downRightY - (int)upLeftY); //Doesn't work for some reason
}

void QtCustomPainter::setStrokeWidth(float width)
{
    m_pen.setWidthF(width);
    onChangePen();
}

void QtCustomPainter::setStrokeColor(const gx::Color &color)
{
    m_pen.setColor(toQColor(color));
    onChangePen();
}

void QtCustomPainter::setBackColor(const gx::Color &color)
{
    m_brush.setColor(toQColor(color));
    onChangeBrush();
}

QColor QtCustomPainter::toQColor(const gx::Color &c)
{
    return QColor(c.r(), c.g(), c.b(), c.a());
}

void QtCustomPainter::onChangePen()
{
    m_painter.setPen(m_pen);
}

void QtCustomPainter::onChangeBrush()
{
    m_painter.setBrush(m_brush);
}
