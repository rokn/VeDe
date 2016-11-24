#ifndef COMMAND_H
#define COMMAND_H

namespace gx
{
class Command
{
public:
    virtual int execute() = 0;
    virtual int undo() = 0;
};
}

#endif // COMMAND_H
