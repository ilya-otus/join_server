#pragma once

class IBulk
{
public:
    virtual void addCommand(const std::string &cmd) = 0;
    virtual void startOfBlock() = 0;
    virtual void endOfBlock() = 0;
    virtual void dumpAll() = 0;
};
