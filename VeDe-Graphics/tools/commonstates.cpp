#include "commonstates.h"
#include "commands/addgobjectcommand.h"
#include "commands/selectcommand.h"

gx::Tool::ToolStateCallBack gx::CommonStates::deleteSelectedObjects(Tool* tool)
{
    return STATE_DEF{
        auto objects = tool->getCanvas()->getSelectedObjects();
        if(objects.size() > 0){
            CanvasCommand* removeObjects = new AddGObjectCommand(false);
            removeObjects->setCanvas(tool->getCanvas());
            removeObjects->setObjects(objects);
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
            tool->getCanvas()->clearSelectedObjects();
            CanvasCommand* selectObjects = new SelectCommand();
            selectObjects->setCanvas(tool->getCanvas());
            selectObjects->setObjects(objects);
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
