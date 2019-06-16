#include "truncate_handler.h"

namespace {
    const std::string cmdName = "TRUNCATE";
} // namespace

TruncateHandler::TruncateHandler(Storage *storage)
    : Handler(storage)
{
}

std::string TruncateHandler::execute() {
    using namespace std::string_literals;
    if (mArgs.size() != 1) {
        return "ERR wrong args"s;
    }
    std::string tableName = mArgs[0];
    return mStorage->truncate(tableName);
}

std::string TruncateHandler::commandName() {
    return cmdName;
}
