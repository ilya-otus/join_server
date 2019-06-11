#include "session.h"
#include <iostream>


namespace {
    const std::string lbrace{"{"};
    const std::string rbrace{"}"};
} // namespace

BulkSession::BulkSession(Socket socket, async::handle_t &bulkHandle)
    : mSocket(std::move(socket)),
    mStarted(false),
    mBulkHandle(bulkHandle),
    mBraceCounter(0)
{
}

void BulkSession::start() {
    mStarted = true;
    doRead();
}

void BulkSession::stop() {
    if (!mStarted) {
        return;
    }
    mStarted = false;
    mSocket.close();
}

void BulkSession::doRead() {
    using namespace std::placeholders;
    async_read_until(mSocket, mStreamBuffer, '\n',
                     std::bind(&BulkSession::onRead, shared_from_this(), _1, _2));
}

void BulkSession::onRead(const error_code &error, size_t bytes) {
    if (error) {
        std::cerr << "On read: " << error.message() << std::endl;
        stop();
        return;
    }
    if (bytes == 0) {
        stop();
    }
    std::string cmd{
        buffers_begin(mStreamBuffer.data()),
        buffers_begin(mStreamBuffer.data()) + bytes
    };
    handleCommand(cmd);
    mStreamBuffer.consume(bytes);
    if (mStreamBuffer.size() != 0) {
        doRead();
    } else {
        stop();
    }
}

void BulkSession::handleCommand(const std::string &cmd) {
    if (cmd.substr(0, cmd.size()-1) == lbrace) {
        ++mBraceCounter;
        mBlock += cmd;
    } else if (cmd.substr(0, cmd.size()-1) == rbrace) {
        --mBraceCounter;
        mBlock += cmd;
        if (!mBlock.empty() && mBraceCounter == 0) {
            receive(mBulkHandle, mBlock.c_str(), mBlock.size());
            mBlock.clear();
        }
    } else if (mBraceCounter != 0) {
        mBlock += cmd;
    } else {
        receive(mBulkHandle, cmd.c_str(), cmd.size());
    }
}
