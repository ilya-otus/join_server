#include "insert_handler.h"

namespace {
    const std::string cmdName = "INSERT";
} // namespace

InsertHandler::InsertHandler(Storage *storage)
    : Handler(storage)
{
}

std::string InsertHandler::execute() {
    using namespace std::string_literals;
    if (mArgs.size() != 3) {
        return "ERR wrong args"s;
    }
    std::string tableName = mArgs[0];
    int id = 0;
    try {
        id = stoi(mArgs[1]);
    } catch (const std::exception &) {
        return "ERR wrong args"s;
    }
    std::string name = mArgs[2];
    return mStorage->insert(tableName, id, name);
}

std::string InsertHandler::commandName() {
    return cmdName;
}
