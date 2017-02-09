#include "path.h"
#include "converters.h"
#include "helpers.h"
#include "graphics_exceptions.h"
#include <QPainterPath>
#include <QPointF>

gx::Path::Path()
{
    onChange() += [this](const gx::GObject* o){
        this->constructPath();
    };
    m_closed = false;
}

void gx::Path::addPoint(gx::Vertex vertex)
{
    preChange();
    m_vertices.append(vertex);
    m_controls.append(false);
    changed();
}

void gx::Path::changeLastPoint(gx::Vertex vertex)
{
    preChange();
    if(m_controls.last())
    {
        m_vertices.replace(m_vertices.size() - 2, vertex);
    }
    else
    {
        m_vertices.last() = vertex;
    }
    changed();
}

void gx::Path::removeLastPoint()
{
    preChange();
    if(m_controls.last()){
        m_vertices.removeLast();
    }

    m_vertices.removeLast();
    m_controls.removeLast();
    changed();
}

void gx::Path::addControlPoint(Vertex control)
{
    if(m_controls.last()){
        throw ;
    }
    else
    {
        preChange();
        m_controls.last() = true;
        m_vertices.append(control);
        changed();
    }
}

void gx::Path::changeLastControl(Vertex control)
{
    if(m_controls.last()){
        preChange();
        m_vertices.last() = control;
        changed();
    }
}

void gx::Path::removeLastControl()
{
    if(m_controls.last()){
        preChange();
        m_vertices.removeLast();
        m_controls.last() = false;
        changed();
    }
}

void gx::Path::closePath()
{
    m_closed = true;
}

QList<bool> gx::Path::controls() const
{
    return m_controls;
}

const QPainterPath& gx::Path::drawnPath() const
{
    return m_drawnPath;
}

QRectF gx::Path::shapeBoundingBox() const
{
    QRectF rect = m_drawnPath.boundingRect();
    fixBoxForStrokeWidth(rect);
    return getTransform().mapRect(rect);
}

bool gx::Path::shapeContainsPoint(const gx::Vertex &point) const
{
    return getTransform().map(m_drawnPath).contains(Converters::toPoint(point));
}

QList<gx::Vertex> gx::Path::vertices() const
{
    return m_vertices;
}

void gx::Path::constructPath()
{
    m_drawnPath = QPainterPath();
    m_drawnPath.setFillRule(Qt::WindingFill);
    QPointF curr, prev, control1, control2;
    bool hasControl1 = m_controls[0], hasControl2 = false;
    int vIndex = (hasControl1) ? 2 : 1;
    control1 = Converters::toPoint(m_vertices[vIndex - 1]);

    prev = Converters::toPoint(m_vertices[0]);
    m_drawnPath.moveTo(prev);


    for (auto control = m_controls.begin() + 1; control != m_controls.end(); ++control) {
        curr = Converters::toPoint(m_vertices[vIndex]);
        hasControl2 = *control;
        if(hasControl2) {
            control2 = 2 * curr - Converters::toPoint(m_vertices[vIndex+1]);
        } else {
            control2 = curr;
        }

        if(hasControl1 || hasControl2){
            m_drawnPath.cubicTo(control1, control2, curr);
        } else {
            m_drawnPath.lineTo(curr);
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

    if(m_closed) {
        m_drawnPath.closeSubpath();
    }
}
