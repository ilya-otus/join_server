#include "bulk_proxy.h"
#include "bulk.h"
#include "handler_fabric.h"

BulkProxy::BulkProxy(size_t bulkSize = 1) 
    : mBulk(new Bulk(bulkSize)),
    mCommandHandler(makeHandler(HandlerType::Command, mBulk)),
    mBraceHandler(makeHandler(HandlerType::Brace, mBulk))
{
    mBraceHandler->setNext(mCommandHandler);
}

std::istream& operator>>(std::istream &is, BulkProxy &bulkProxy) {
    for (std::string cmd; std::getline(is, cmd); ) {
        bulkProxy.mBraceHandler->handle(cmd);
    }
    return is;
}

std::shared_ptr<IBulk> BulkProxy::bulk() {
    return mBulk;
}
