#pragma once
#include <boost/asio.hpp>
#include <memory>
#include "src/async.h"

using Socket = boost::asio::ip::tcp::socket ;
using StreamBuf = boost::asio::streambuf;

class BulkSession : public std::enable_shared_from_this<BulkSession>
{
public:
    using error_code = boost::system::error_code;

    BulkSession(const BulkSession &) = delete;
    BulkSession& operator=(const BulkSession) = delete;
    BulkSession(Socket socket, async::handle_t &bulkHandle);
    ~BulkSession() = default;
    void start();
private:
    void stop();
    void doRead();
    void onRead(const error_code &error, size_t bytes);
    void handleCommand(const std::string &cmd);
private:
    Socket mSocket;
    bool mStarted;
    StreamBuf mStreamBuffer;
    async::handle_t &mBulkHandle;
    std::string mBlock;
    int mBraceCounter;
};
