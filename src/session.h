#pragma once
#include <boost/asio.hpp>
#include <memory>
#include "storage.h"

using Socket = boost::asio::ip::tcp::socket ;
using StreamBuf = boost::asio::streambuf;

class JoinSession : public std::enable_shared_from_this<JoinSession>
{
public:
    using error_code = boost::system::error_code;

    JoinSession(const JoinSession &) = delete;
    JoinSession& operator=(const JoinSession) = delete;
    JoinSession(Socket socket, Storage &storage);
    ~JoinSession() = default;
    void start();
private:
    void stop();
    void doRead();
    void doWrite(const std::string &data);
    void onRead(const error_code &error, size_t bytes);
    void onWrite(const error_code &error, size_t bytes);
private:
    Socket mSocket;
    bool mStarted;
    StreamBuf mStreamBuffer;
    std::string mBlock;
    Storage &mStorage;
    inline static int id = 0;
    int mSessionId;
};
