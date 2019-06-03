#include "bulk_proxy.h"
#include "bulk.h"
#include "handler_fabric.h"
#include <sstream>

namespace {
template <char D>
class DelimitingHelper : public std::string {
public:
    friend std::istream& operator>>(std::istream &is, DelimitingHelper<D> &dh) {
        std::getline(is, dh, D);
        return is;
    }
};
} // namespace

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

void BulkProxy::appendCommand(const std::string &cmd) {
    mBraceHandler->handle(cmd);
    ++mStrCount;
}

void BulkProxy::operator<<(const std::vector<std::string> &cmds) {
    std::lock_guard<std::mutex> streamGuard(mStreamMutex);
    for (auto cmd = cmds.cbegin(); cmd != cmds.cend(); ++cmd) {
        appendCommand(*cmd);
    }
}

std::istream& operator>>(std::istream &is, BulkProxy &bulkProxy) {
    std::lock_guard<std::mutex> streamGuard(bulkProxy.mStreamMutex);
    for (std::string cmd; std::getline(is, cmd); ) {
        bulkProxy.appendCommand(cmd);
    }
    return is;
}

