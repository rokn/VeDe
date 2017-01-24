#include "path.h"
#include "graphics_exceptions.h"
#include <QPainterPath>

gx::Path::Path()
{
}

void gx::Path::addPoint(gx::Vertex vertex)
{
    m_vertices.append(vertex);
    m_controls.append(false);
    changed();
}

void gx::Path::changeLastPoint(gx::Vertex vertex)
{
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
        m_controls.last() = true;
        m_vertices.append(control);
        changed();
    }
}

void gx::Path::changeLastControl(Vertex control)
{
    if(m_controls.last()){
        m_vertices.last() = control;
        changed();
    }
}

void gx::Path::removeLastControl()
{
    if(m_controls.last()){
        m_vertices.removeLast();
        m_controls.last() = false;
        changed();
    }
}

void gx::Path::paintSelf(gx::CustomPainter &painter)
{
    Shape::paintSelf(painter);
    if(changedSinceDraw()) {
        qInfo() << "redraw";
        m_path = QPainterPath();
        m_path.setFillRule(Qt::WindingFill);
        QPointF curr, prev, control1, control2;
        bool hasControl1 = m_controls[0], hasControl2 = false;
        int vIndex = (hasControl1) ? 2 : 1;
        control1 = QPointF(m_vertices[vIndex - 1].x(), m_vertices[vIndex - 1].y());

        prev = QPointF(m_vertices[0].x(), m_vertices[0].y());
        m_path.moveTo(prev);


        for (auto control = m_controls.begin() + 1; control != m_controls.end(); ++control) {
            curr = QPointF(m_vertices[vIndex].x(), m_vertices[vIndex].y());
            hasControl2 = *control;
            if(hasControl2) {
                control2 = 2 * curr - QPointF(m_vertices[vIndex+1].x(), m_vertices[vIndex+1].y());
            } else {
                control2 = curr;
            }

            if(hasControl1 || hasControl2){
                m_path.cubicTo(control1, control2, curr);
            } else {
                m_path.lineTo(curr);
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

    }
    painter.drawPath(m_path);
}
