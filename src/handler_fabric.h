#pragma once
#include "brace_handler.h"
#include "command_handler.h"

enum class HandlerType {
    Brace,
    Command
};

std::shared_ptr<Handler> makeHandler(HandlerType type, std::shared_ptr<IBulk> bulk);
