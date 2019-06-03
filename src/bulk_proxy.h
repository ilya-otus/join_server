#pragma once
#include <istream>
#include <memory>
#include "bulk_interface.h"
#include <mutex>

class Handler;
class BulkProxy
{
public:
    BulkProxy(size_t bulkSize);
    ~BulkProxy();
    void operator<<(const std::vector<std::string> &cmds);
    friend std::istream& operator>>(std::istream &is, BulkProxy &bulkProxy);
private:
    void appendCommand(const std::string &cmd);
private:
    std::shared_ptr<IBulk> mBulk;
    std::shared_ptr<Handler> mCommandHandler;
    std::shared_ptr<Handler> mBraceHandler;
    size_t mStrCount = 0;
    std::mutex mStreamMutex;
};
