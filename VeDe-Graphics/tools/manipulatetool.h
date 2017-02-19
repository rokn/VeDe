#ifndef MANIPULATETOOL_H
#define MANIPULATETOOL_H

#include "tool.h"
#include "commands/canvascommand.h"
#include <QRectF>

namespace gx
{
class ManipulateTool : public Tool
{
public:
    ManipulateTool(Canvas* canvas);
    ~ManipulateTool();

    void drawGui(CustomPainter& painter) const;

private:
    class ManipulateMode;
    ManipulateMode* m_currMode;
    bool m_inManipulation;

    class ManipulateMode
    {
    public:
        virtual ~ManipulateMode(){}
        virtual void startManipulation(Vertex cursor) = 0;
        virtual void updateManipulation(Vertex cursor, SharedGObject obj) = 0;
        virtual void postUpdate(Vertex cursor) = 0;
        virtual CanvasCommand* endManipulation() = 0;
        virtual void drawGui(CustomPainter& painter) const;
        Canvas* getCanvas();
        Canvas* getCanvas() const;
        void setCanvas(Canvas* canvas);

    protected:
        Canvas* m_canvas;
    };


    class SelectionMode : public ManipulateMode
    {
    public:
        void startManipulation(Vertex cursor);
        void updateManipulation(Vertex cursor, SharedGObject obj);
        void postUpdate(Vertex cursor);
        CanvasCommand* endManipulation();
        void drawGui(CustomPainter& painter) const;

    private:
        Vertex m_anchorPoint;
        QRectF m_selection;
    };

    class TranslationMode : public ManipulateMode
    {
    public:
        void startManipulation(Vertex cursor);
        void updateManipulation(Vertex cursor, SharedGObject obj);
        void postUpdate(Vertex cursor);
        CanvasCommand* endManipulation();

    private:
        Vertex m_startPosition;
        Vertex m_lastPosition;

    };

    class RotationMode : public ManipulateMode
    {
    public:
        void startManipulation(Vertex cursor);
        void updateManipulation(Vertex cursor, SharedGObject obj);
        void postUpdate(Vertex cursor);
        CanvasCommand* endManipulation();
        void drawGui(CustomPainter& painter) const;

    private:
        Vertex m_startPosition;
        Vertex m_rotationAxis;
        Vertex m_oldPosition;
        double m_oldAngle;
        double m_totalRotation;
        bool m_useRotAxis;
    };

    class ScaleMode : public ManipulateMode
    {
    public:
        void startManipulation(Vertex cursor);
        void updateManipulation(Vertex cursor, SharedGObject obj);
        void postUpdate(Vertex cursor);
        CanvasCommand* endManipulation();
        void drawGui(CustomPainter& painter) const;

    private:
        Vertex m_startPosition;
        Vertex m_scaleAxis;
        Vertex m_oldPosition;
        bool m_useRotAxis;
    };
};
}

#endif // MANIPULATETOOL_H
