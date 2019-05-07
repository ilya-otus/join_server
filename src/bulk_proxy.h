#pragma once
#include <istream>
#include <memory>
#include "bulk_interface.h"

class Handler;
class BulkProxy
{
public:
    BulkProxy(size_t bulkSize);
    friend std::istream& operator>>(std::istream &is, BulkProxy &bulkProxy);
    std::shared_ptr<IBulk> bulk();
private:
    std::shared_ptr<IBulk> mBulk;
    std::shared_ptr<Handler> mCommandHandler;
    std::shared_ptr<Handler> mBraceHandler;
};
