#ifndef COMMONSTATES_H
#define COMMONSTATES_H

#include "tool.h"

namespace gx
{
namespace CommonStates
{
    Tool::ToolStateCallBack deleteSelectedObjects(Tool *tool);
    Tool::ToolStateCallBack selectAllOnCurrLayer(Tool *tool);
    Tool::ToolStateCallBack deselectAll(Tool *tool);
}
}

#endif // COMMONSTATES_H
