#include "src/async.h"
#include "server.h"
#include <iostream>
#include <csignal>

int main(int argc, char **argv) {
    int bulkSize = 1;
    int port = 9999;
    if (argc > 1) {
        if (int prt = std::atoi(argv[1]); prt != 0) {
            port = prt;
        }
    }
    if (argc > 2) {
        if (int bs = std::atoi(argv[2]); bs != 0) {
            bulkSize = bs;
        }
    }
    try {
        IOContext context;
        auto server = std::make_shared<BulkServer>(context, port, bulkSize);

        boost::asio::signal_set signals(context, SIGINT);
        auto signalHandler = [&server, &context] (const boost::system::error_code &error, int) {
            if (error) {
                std::cerr << "Signal handler: " << error.message() << std::endl;
                exit(1);
            }
            context.stop();
            server.reset();
            exit(0);
        };
        signals.async_wait(signalHandler);

        context.run();
    } catch (const std::exception &exception) {
        std::cerr << exception.what() << std::endl;
    }
    return 0;
}
