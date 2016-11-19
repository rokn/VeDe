#include "line.h"

Line::Line()
{
}

Line::Line(Vertex start, Vertex end)
    :_start(start), _end(end)
{
}

void Line::drawSelf(QPaintEvent *event, QPaintDevice *device)
{
    QPainter p(device);
    p.setPen(*getProp<ColorProperty>("stroke-color"));
    p.drawLine(_start, _end);
}

//p = gobject.getProperty("dd").getType().

//Property
//         - PropertyValue
//            StringPropertyValue.getValue()
//            IntPropertyValue.getValue()
//            IntPropertyValue.getType()

//        .getIntValue()
//            if(pv.getType()=="INT")
//                   pv.getValue()
//            else
//                throw
