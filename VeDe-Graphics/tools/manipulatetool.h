#ifndef MANIPULATETOOL_H
#define MANIPULATETOOL_H

#include "tool.h"
#include <QRectF>

namespace gx
{
class ManipulateTool : public Tool
{
public:
    ManipulateTool(Canvas* canvas);

    void drawGui(CustomPainter& painter) const;

private:
    class ManipulateMode;
    ManipulateMode* m_currMode;

    QRectF m_selection;
    Vertex m_anchorPoint;
    Vertex m_rotationAxis;
    double m_oldAngle;
    double m_totalRotation;
    bool m_oldAngleSet;
    bool m_useRotAxis;
    bool m_selecting;
    bool m_translating;
    bool m_rotating;
    bool m_scaling;
    bool m_union;

    void selectObjects(QRectF rect);

    void updateSelection(Vertex cursor);
    void updateTranslation(Vertex cursor);
    void updateRotation(Vertex cursor);
    void updateScaling(Vertex cursor);

    void endSelection();
    void endTranslation();
    void endRotation();

    class ManipulateMode
    {
        Qt::Key getEnterKey() const;
        virtual void startManipulation(Vertex cursor) = 0;
        virtual void updateManipulation(Vertex cursor) = 0;
        virtual void postUpdate(Vertex cursor) = 0;
        virtual void endManipulation(Vertex cursor) = 0;

    protected:
        Qt::Key m_enterKey;
    };

    class TranslationMode : public ManipulateMode
    {
        TranslationMode():m_enterKey(Qt::Key_W){}
        void startManipulation(Vertex cursor);
        void updateManipulation(Vertex cursor);
        void postUpdate(Vertex cursor) = 0;
        void endManipulation(Vertex cursor);

    private:
        Vertex m_startPosition;
        Vertex m_lastPosition;

    };
};
}

#endif // MANIPULATETOOL_H
