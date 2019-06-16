#include "server.h"
#include <iostream>

using namespace boost::asio;

JoinServer::JoinServer(IOContext &context, int port)
    : mAcceptor(context, ip::tcp::endpoint(ip::tcp::v4(), port)),
    mStorage()
{
    doAccept();
}

void JoinServer::doAccept() {
    using namespace std::placeholders;
    mAcceptor.async_accept(std::bind(&JoinServer::onAccept, this, _1, _2));
}
void JoinServer::onAccept(const error_code &error, Socket socket) {
    if (error) {
        std::cerr << "On accept: " << error.message() << std::endl;
    } else {
        std::make_shared<JoinSession>(std::move(socket), mStorage)->start();
    }
    doAccept();
}
