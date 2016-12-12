#ifndef CURRTOOLTOOLBAR_H
#define CURRTOOLTOOLBAR_H

#include <QToolBar>
#include <QLabel>
#include "tools/tool.h"

class CurrToolToolbar : public QToolBar
{
    Q_OBJECT
public:
    CurrToolToolbar(gx::Canvas* canvas, QWidget *parent = 0);

public slots:
    void canvasToolChanged(gx::Tool* newTool);


private:
    QLabel* m_nameLabel;
    QList<QWidget*> m_propertyWidgets;
};

#endif // CURRTOOLTOOLBAR_H
