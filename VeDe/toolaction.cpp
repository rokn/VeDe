#include "toolaction.h"

ToolAction::ToolAction(gx::Tool *tool, QObject* parent)
    :QAction(tool->getName(), parent), m_tool(tool)
{
    connect(this, &QAction::triggered, this, &ToolAction::onTriggered);
}

void ToolAction::onTriggered(bool checked)
{
    if(checked) {
        m_tool->switchTo();
    }
}
