#include "server.h"
#include <iostream>

using namespace boost::asio;

BulkServer::BulkServer(IOContext &context, int port, int bulkSize)
    : mAcceptor(context, ip::tcp::endpoint(ip::tcp::v4(), port))
{
    doAccept();
    mBulkHandle = async::connect(bulkSize);
}

BulkServer::~BulkServer() {
    disconnect(mBulkHandle);
}

void BulkServer::doAccept() {
    using namespace std::placeholders;
    mAcceptor.async_accept(std::bind(&BulkServer::onAccept, this, _1, _2));
}
void BulkServer::onAccept(const error_code &error, Socket socket) {
    if (error) {
        std::cerr << "On accept: " << error.message() << std::endl;
    } else {
        std::make_shared<BulkSession>(std::move(socket), mBulkHandle)->start();
    }
    doAccept();
}
