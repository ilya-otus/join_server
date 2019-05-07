#pragma once
#include <memory>
#include "bulk_interface.h"

class Handler
{
public:
    Handler(std::shared_ptr<IBulk> bulk);
    void setNext(std::shared_ptr<Handler> next);
    void add(std::shared_ptr<Handler> next);
    virtual void handle(const std::string &cmd);

protected:
    void startOfBlock();
    void endOfBlock();
    void addCommand(const std::string &cmd);

private:
    std::shared_ptr<Handler> mNext;
    std::shared_ptr<IBulk> mBulk;
};

