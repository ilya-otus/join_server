#pragma once
#include <boost/asio.hpp>
#include "session.h"

using IOContext = boost::asio::io_context;
using Acceptor = boost::asio::ip::tcp::acceptor;

class JoinServer
{
public:
    JoinServer(IOContext &context, int port);
    ~JoinServer() = default;
private:
    using error_code = boost::system::error_code;
    void doAccept();
    void onAccept(const error_code &error, Socket socket);
private:
    Acceptor mAcceptor;
    Storage mStorage;
};
