#ifndef RESTRICTABLETOOL_H
#define RESTRICTABLETOOL_H

#include "tool.h"

namespace gx
{
class RestrictableTool : public Tool
{
public:
    RestrictableTool(Canvas* canvas);
protected:
    bool isRestricted() const;
    void setRestricted(bool restricted);
    void setUpRestriction(gx::Tool::ToolStateCallBack onChange);

private:
    bool m_restricted;
};
}

#endif // RESTRICTABLETOOL_H
