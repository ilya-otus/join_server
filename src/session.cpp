#include "session.h"
#include <iostream>

JoinSession::JoinSession(Socket socket, Storage &storage)
    : mSocket(std::move(socket)),
    mStarted(false),
    mStorage(storage),
    mSessionId(id++)
{
}

void JoinSession::start() {
    mStarted = true;
    doRead();
}

void JoinSession::stop() {
    if (!mStarted) {
        return;
    }
    mStorage.onSessionFinished(mSessionId);
    mStarted = false;
    mSocket.close();
}

void JoinSession::doRead() {
    using namespace std::placeholders;
    async_read_until(mSocket, mStreamBuffer, '\n',
                     std::bind(&JoinSession::onRead, shared_from_this(), _1, _2));
}

void JoinSession::onRead(const error_code &error, size_t bytes) {
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
        buffers_begin(mStreamBuffer.data()) + bytes - 1
    };
    mStorage.addCommand(mSessionId, cmd, [this](const std::string &response) {
                         doWrite(response);
    });
    mStreamBuffer.consume(bytes);
    if (mStreamBuffer.size() != 0) {
        doRead();
    } else {
        stop();
    }
}

void JoinSession::doWrite(const std::string &data) {
    using namespace std::placeholders;
    async_write(mSocket, boost::asio::buffer(data + '\n'),
                std::bind(&JoinSession::onWrite, shared_from_this(), _1, _2));
}

void JoinSession::onWrite(const error_code &error, size_t bytes) {
    if (error) {
        std::cerr << "On write: " << error.message() << std::endl;
        stop();
        return;
    }
    std::cerr << bytes << " bytes written" << std::endl;
    stop();
}
