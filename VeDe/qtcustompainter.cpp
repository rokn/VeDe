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

void QtCustomPainter::drawLine(double x1, double y1, double x2, double y2)
{
    m_painter->drawLine(QPointF(x1, y1), QPointF(x2, y2));
}

void QtCustomPainter::drawEllipse(double cX, double cY, double rX, double rY)
{
    m_painter->drawEllipse(QPointF(cX, cY), rX, rY);
}

void QtCustomPainter::drawRectangle(double upLeftX, double upLeftY, double downRightX, double downRightY)
{
    QRectF rect(QPointF(upLeftX, upLeftY), QPointF(downRightX, downRightY));
    m_painter->drawRect(rect);
    //Doesn't work for some reason
}

void QtCustomPainter::drawPath(QList<gx::Vertex> vertices, QList<bool> controls)
{
    QPainterPath path;
    path.setFillRule(Qt::WindingFill);
    QPointF curr, prev, control1, control2;
    bool hasControl1 = controls[0], hasControl2 = false;
    int vIndex = (hasControl1) ? 2 : 1;
    control1 = gx::Converters::toPoint(vertices[vIndex - 1]);

    prev = gx::Converters::toPoint(vertices[0]);
    path.moveTo(prev);


    for (auto control = controls.begin() + 1; control != controls.end(); ++control) {
        curr = gx::Converters::toPoint(vertices[vIndex]);
        hasControl2 = *control;
        if(hasControl2) {
            control2 = 2 * curr - gx::Converters::toPoint(vertices[vIndex+1]);
        } else {
            control2 = curr;
        }

        if(hasControl1 || hasControl2){
            path.cubicTo(control1, control2, curr);
        } else {
            path.lineTo(curr);
        }

        hasControl1 = hasControl2;
        control1 = control2;
        prev = curr;

        if(hasControl2) {
            vIndex += 2;
            control1 = 2 * curr - control1;
        } else {
            vIndex ++;
        }
    }

    m_painter->drawPath(path);
}

void QtCustomPainter::drawPath(QPainterPath &path)
{
    m_painter->drawPath(path);
}

void QtCustomPainter::setStrokeWidth(double width)
{
    m_pen.setWidthF(width);
    onChangePen();
}

void QtCustomPainter::setStrokeColor(const gx::Color &color)
{
    m_pen.setColor(gx::Converters::toQColor(color));
    onChangePen();
}

void QtCustomPainter::setBackColor(const gx::Color &color)
{
    m_brush.setColor(gx::Converters::toQColor(color));
    onChangeBrush();
}

void QtCustomPainter::setZoomFactor(double zoomFactor)
{
    m_painter->scale(zoomFactor, zoomFactor);
}

void QtCustomPainter::setTransform(QTransform transform)
{
    m_oldTransform = m_painter->transform();
    m_painter->setTransform(transform * m_oldTransform);
}

void QtCustomPainter::resetTransform()
{
    m_painter->setTransform(m_oldTransform);
}

void QtCustomPainter::onChangePen()
{
    m_painter->setPen(m_pen);
}

void QtCustomPainter::onChangeBrush()
{
    m_painter->setBrush(m_brush);
}

void QtCustomPainter::setPainter(QPainter *painter)
{
    m_painter = painter;
}
