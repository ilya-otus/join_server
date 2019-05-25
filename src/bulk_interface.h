#pragma once
#include <vector>
using Metrics = std::tuple<size_t, size_t>;

class IBulk
{
public:
    virtual void addCommand(const std::string &cmd) = 0;
    virtual void startOfBlock() = 0;
    virtual void endOfBlock() = 0;
    virtual Metrics metrics() const = 0;
};
