#include "addgobjectcommand.h"

gx::AddGObjectCommand::AddGObjectCommand(bool add)
    :m_add(add)
{
}

int gx::AddGObjectCommand::execute()
{
    foreach(auto& obj, m_objects)
    {
        if(m_add){
            getCanvas()->addToCurrLayer(obj);
        } else {
            obj->remove();
        }
    }

    return 0;
}

int gx::AddGObjectCommand::undo()
{
    foreach(auto& obj, m_objects)
    {
        if(m_add){
            obj->remove();
        } else {
            getCanvas()->addToCurrLayer(obj);
        }
    }
    return 0;
}
