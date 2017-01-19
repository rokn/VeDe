#include "qtcustompainter.h"
#include "converters.h"
#include <QRgb>
#include <QDebug>
#include <QPainterPath>

QtCustomPainter::QtCustomPainter(QPainter *painter)
    :m_painter(painter)
{
    m_pen.setJoinStyle(Qt::MiterJoin);
    m_brush.setStyle(Qt::SolidPattern);
    m_painter->setRenderHint(QPainter::Antialiasing);
    m_painter->setBackgroundMode(Qt::OpaqueMode);
}

void QtCustomPainter::drawLine(float x1, float y1, float x2, float y2)
{
    m_painter->drawLine(QPointF(x1, y1), QPointF(x2, y2));
}

void QtCustomPainter::drawEllipse(float cX, float cY, float rX, float rY)
{
    m_painter->drawEllipse(QPointF(cX, cY), rX, rY);
}

void QtCustomPainter::drawRectangle(float upLeftX, float upLeftY, float downRightX, float downRightY)
{
    QRectF rect(QPointF(upLeftX, upLeftY), QPointF(downRightX, downRightY));
    m_painter->drawRect(rect);
    //Doesn't work for some reason
}

void QtCustomPainter::drawPath(QList<gx::Vertex> vertices, QList<int> moves)
{
    QPainterPath path;
    QPointF end, control, control2;
    path.moveTo(vertices[0].x(), vertices[0].y());
    int vIndex = 1;

    foreach (int move, moves) {
        switch(move){
            case -1:
                path.closeSubpath();
                break;
            case 0:
                path.lineTo(vertices[vIndex].x(), vertices[vIndex].y());
                vIndex++;
                break;
            case 1:
            //Remove logic
                end = QPointF(vertices[vIndex].x(), vertices[vIndex].y());
                vIndex++;
                control = QPointF(vertices[vIndex].x(), vertices[vIndex].y());
                vIndex++;
                control = end + (end - control);
                path.cubicTo(control, control, end);
                break;
            case 2:
                control = QPointF(vertices[vIndex].x(), vertices[vIndex].y());
                vIndex++;
                end = QPointF(vertices[vIndex].x(), vertices[vIndex].y());
                vIndex++;
                control2 = QPointF(vertices[vIndex].x(), vertices[vIndex].y());
                vIndex++;
                path.cubicTo(control, control2, end);
                break;
        }
    }

    m_painter->drawPath(path);
}

void QtCustomPainter::setStrokeWidth(float width)
{
    m_pen.setWidthF(width);
    onChangePen();
}

void QtCustomPainter::setStrokeColor(const gx::Color &color)
{
    m_pen.setColor(Converters::toQColor(color));
    onChangePen();
}

void QtCustomPainter::setBackColor(const gx::Color &color)
{
    m_brush.setColor(Converters::toQColor(color));
    onChangeBrush();
}

void QtCustomPainter::setZoomFactor(float zoomFactor)
{
    m_painter->scale(zoomFactor, zoomFactor);
}

void QtCustomPainter::onChangePen()
{
    m_painter->setPen(m_pen);
}

void QtCustomPainter::onChangeBrush()
{
    m_painter->setBrush(m_brush);
}
