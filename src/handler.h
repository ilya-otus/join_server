#pragma once
#include <memory>
#include <vector>
#include "storage.h"

class Handler {
public:
    Handler() = default;
    virtual ~Handler() = default;
    void setArgs(const std::vector<std::string> &cmdArgs);
    void handle(std::function<void(std::string)> callback);
protected:
    virtual std::string execute() = 0;
protected:
    Handler(Storage *storage);
    std::vector<std::string> mArgs;
    Storage *mStorage;
};
