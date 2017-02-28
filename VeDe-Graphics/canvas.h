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
#include <Qt>

namespace gx
{
//Forward decl.
class Tool;

class Canvas : public PropertyHolder
{
//    Q_OBJECT
public:
    Canvas(SharedGObject root = nullptr, double width = 800.0, double height = 600.0);
    virtual ~Canvas();

    SharedGObject root();

    virtual Vertex getCursor() const = 0;

    virtual bool isKeyPressed(Qt::Key key) const = 0;

    int executeCommand(Command* command);

    void addSilentCommand(Command* command);

    int undoCommand();

    int redoCommand();

    void handleTransition(const UserEvent &transition);

    virtual void redraw() = 0;
    virtual void redrawGui() = 0;
    virtual void redraw(QRectF area) = 0;

    void addToCurrLayer(SharedGObject object);

    void changeCurrTool(Tool* newTool);

    std::shared_ptr<Layer> getCurrLayer() const;

    double getZoomFactor() const;
    void setZoomFactor(double zoomFactor);

    double mapValueToZoom(double value) const;

    virtual void onAddObject(SharedGObject object);

    Tool *getCurrTool() const;

    double getWidth() const;
    void setWidth(double width);

    double getHeight() const;
    void setHeight(double height);
    Event<Tool*>& onToolChanged();

    Event<double>& onZoomChange();

    bool isLocked() const;
    void lock();
    void unlock();

    QList<SharedGObject> getSelectedObjects();
    QRectF getSelectedObjectsBox();
    void clearSelectedObjects(bool withCommand = true);
    void selectObject(SharedGObject obj);
    void deselectObject(SharedGObject obj);

    QRectF getBoundaries() const;

private:
    SharedGObject m_root;
    QVector<Command*> m_commandHistory;
    QList<SharedGObject> m_selectedObjects;
    unsigned int m_currCommand;
    Tool* m_currTool;
    std::shared_ptr<Layer> m_currLayer;
    unsigned int m_idCount;
    double m_zoomFactor;
    double m_width;
    double m_height;
    bool m_locked;
    Event<Tool*> m_onToolChanged;
    Event<double> m_onZoomChange;

    void addNewCommand(Command* command);
};
}

#endif // CANVAS_H
