#include "commonstates.h"
#include "commands/addgobjectcommand.h"
#include "commands/selectcommand.h"

gx::Tool::ToolStateCallBack gx::CommonStates::deleteSelectedObjects(Tool* tool)
{
    return STATE_DEF{
        auto objects = tool->getCanvas()->getSelectedObjects();
        if(objects.size() > 0){
            Command* removeObjects = new AddGObjectCommand(objects, tool->getCanvas(), false);
            tool->getCanvas()->executeCommand(removeObjects);
        }
        tool->moveToStateSilent(tool->getLastState());
    };
}

gx::Tool::ToolStateCallBack gx::CommonStates::selectAllOnCurrLayer(gx::Tool *tool)
{
    return STATE_DEF{
        auto objects = tool->getCanvas()->getCurrLayer()->getChildren();
        if(objects.size() > 0){
            Command* selectObjects = new SelectCommand(objects, tool->getCanvas());
            tool->getCanvas()->executeCommand(selectObjects);

        }
        tool->moveToStateSilent(tool->getLastState());
    };
}

gx::Tool::ToolStateCallBack gx::CommonStates::deselectAll(gx::Tool *tool)
{
    return STATE_DEF{
        tool->getCanvas()->clearSelectedObjects();
        tool->moveToStateSilent(tool->getLastState());
    };
}
