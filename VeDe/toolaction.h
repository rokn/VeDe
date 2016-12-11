#ifndef TOOLACTION_H
#define TOOLACTION_H

#include <QAction>
#include <memory>
#include "tools/tool.h"

class ToolAction : public QAction
{
public:
    ToolAction(gx::Tool* tool, QObject* parent = nullptr);

public slots:
    void onTriggered(bool checked = false);
private:
    std::unique_ptr<gx::Tool> m_tool;
};

#endif // TOOLACTION_H
