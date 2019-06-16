#include "parser.h"
#include <sstream>

#include "insert_handler.h"
#include "intersection_handler.h"
#include "storage.h"
#include "symmetric_difference_handler.h"
#include "truncate_handler.h"
#include <boost/algorithm/string.hpp>

Parser::Parser(Storage *storage)
    : mStorage(storage)
{ }

std::unique_ptr<Handler> Parser::parse(const std::string &command) const {
    std::istringstream parseStream(command);
    std::string cmd;
    std::vector<std::string> commandArgs;
    while (std::getline(parseStream, cmd, ' ')) {
        commandArgs.push_back(cmd);
    }
    std::unique_ptr<Handler> result(nullptr);
    if (commandArgs[0] == InsertHandler::commandName()) {
        result.reset(new InsertHandler(mStorage));
    } else if (commandArgs[0] == IntersectionHandler::commandName()) {
        result.reset(new IntersectionHandler(mStorage));
    } else if (commandArgs[0] == SymmetricDifferenceHandler::commandName()) {
        result.reset(new SymmetricDifferenceHandler(mStorage));
    } else if (commandArgs[0] == TruncateHandler::commandName()) {
        result.reset(new TruncateHandler(mStorage));
    }
    result->setArgs({commandArgs.begin()+1, commandArgs.end()});
    return result;
}
