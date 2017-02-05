#include "restrictabletool.h"

gx::RestrictableTool::RestrictableTool(gx::Canvas *canvas)
    :Tool(canvas)
{
    m_restricted = false;
}

bool gx::RestrictableTool::isRestricted() const
{
    return m_restricted;
}

void gx::RestrictableTool::setRestricted(bool restricted)
{
    m_restricted = restricted;
}

void gx::RestrictableTool::setUpRestriction(gx::Tool::ToolStateCallBack onChange)
{
    QString restrictState = "Restrict";
    QString unRestrictState = "UnRestrict";

    addState(restrictState, STATE_DEF{
        m_restricted = true;
        onChange(t);
        moveToStateSilent(getLastState());
    });

    addState(unRestrictState, STATE_DEF{
        m_restricted = false;
        onChange(t);
        moveToStateSilent(getLastState());
    });

    addTransition(ANY_STATE, UserEvent(KEY_PRESS, Qt::Key_Shift), restrictState);
    addTransition(ANY_STATE, UserEvent(KEY_RELEASE, Qt::Key_Shift), unRestrictState);
}
