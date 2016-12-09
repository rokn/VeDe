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
    void setUpRestriction(const QString& from, Tool::ToolStateCallBack onChange);

private:
    bool m_restricted;
};
}

#endif // RESTRICTABLETOOL_H
