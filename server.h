#pragma once
#include <boost/asio.hpp>
#include "src/async.h"
#include "session.h"

using IOContext = boost::asio::io_context;
using Acceptor = boost::asio::ip::tcp::acceptor;

class BulkServer
{
public:
    BulkServer(IOContext &context, int port, int bulkSize);
    ~BulkServer();
private:
    using error_code = boost::system::error_code;
    void doAccept();
    void onAccept(const error_code &error, Socket socket);
private:
    Acceptor mAcceptor;
    async::handle_t mBulkHandle;
};
