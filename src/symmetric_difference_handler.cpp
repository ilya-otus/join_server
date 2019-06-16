#include "symmetric_difference_handler.h"

namespace {
    const std::string cmdName = "SYMMETRIC_DIFFERENCE";
} // namespace

SymmetricDifferenceHandler::SymmetricDifferenceHandler(Storage *storage)
    : Handler(storage)
{
}

std::string SymmetricDifferenceHandler::execute() {
    return mStorage->symmetricDifference();
}

std::string SymmetricDifferenceHandler::commandName() {
    return cmdName;
}
