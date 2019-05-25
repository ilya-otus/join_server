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

BulkProxy::~BulkProxy() {
    mCommandHandler.reset();
    mBraceHandler.reset();
    auto [blocks, cmds] = mBulk->metrics();
    mBulk.reset();
    std::cout << "Total processed in Main thread: "
        << mStrCount << " strings, "
        << blocks << " blocks and "
        << cmds << " commands"<< std::endl;
}

std::istream& operator>>(std::istream &is, BulkProxy &bulkProxy) {
    for (std::string cmd; std::getline(is, cmd); ) {
        bulkProxy.mBraceHandler->handle(cmd);
        ++bulkProxy.mStrCount;
    }
    return is;
}

