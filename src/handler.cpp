#include "handler.h"
#include <iostream>

Handler::Handler(Storage *storage)
    : mStorage(storage)
{
}

void Handler::setArgs(const std::vector<std::string> &cmdArgs) {
    mArgs = cmdArgs;
}

void Handler::handle(std::function<void(std::string)> callback) {
    callback(execute());
}
