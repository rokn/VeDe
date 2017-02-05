#ifndef CANVAS_H
#define CANVAS_H

#include "tools/userevent.h"
#include "objects/gobject.h"
#include "objects/rectangle.h"
#include "layer.h"
#include "event.h"
#include "commands/command.h"
#include <memory>
#include <QVector>
#include <QList>
#include <QEvent>
#include <QRectF>

namespace gx
{
//Forward decl.
class Tool;

class Canvas : public PropertyHolder
{
//    Q_OBJECT
public:
    Canvas(std::shared_ptr<GObject> root = nullptr, QObject* parent = 0);
    virtual ~Canvas();

    std::shared_ptr<GObject> root();

    virtual Vertex getCursor() const = 0;

    int executeCommand(Command* command);

    int undoCommand();

    int redoCommand();

    void handleTransition(const UserEvent &transition);

    virtual void redraw() = 0;
    virtual void redrawGui() = 0;
    virtual void redraw(QRectF area) = 0;

    void addToCurrLayer(std::shared_ptr<GObject> object);

    void changeCurrTool(Tool* newTool);

    std::shared_ptr<Layer> getCurrLayer() const;

    float getZoomFactor() const;
    void setZoomFactor(float zoomFactor);

    virtual void onAddObject(std::shared_ptr<GObject> object);

    Tool *getCurrTool() const;

    float getWidth() const;
    void setWidth(float width);

    float getHeight() const;
    void setHeight(float height);

    Event<Tool*>& onToolChanged();

    Event<float>& onZoomChange();

    bool isLocked() const;
    void lock();
    void unlock();

    QList<std::shared_ptr<GObject>> getSelectedObjects();
    void clearSelectedObjects();
    void selectObject(std::shared_ptr<GObject> obj);
    void deselectObject(std::shared_ptr<GObject> obj);

private:
    std::shared_ptr<GObject> m_root;
    QVector<Command*> m_commandHistory;
    QList<std::shared_ptr<GObject>> m_selectedObjects;
    unsigned int m_currCommand;
    Tool* m_currTool;
    std::shared_ptr<Layer> m_currLayer;
    unsigned int m_idCount;
    float m_zoomFactor;
    float m_width;
    float m_height;
    bool m_locked;
    Event<Tool*> m_onToolChanged;
    Event<float> m_onZoomChange;
};
}

#endif // CANVAS_H
