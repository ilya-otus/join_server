#include "intersection_handler.h"

namespace {
    const std::string cmdName = "INTERSECTION";
} // namespace

IntersectionHandler::IntersectionHandler(Storage *storage)
    : Handler(storage)
{
}

std::string IntersectionHandler::execute() {
    return mStorage->intersection();
}

std::string IntersectionHandler::commandName() {
    return cmdName;
}
