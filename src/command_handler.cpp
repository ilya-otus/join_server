#include "command_handler.h"

CommandHandler::CommandHandler(std::shared_ptr<IBulk> bulk)
    : Handler(bulk)
{
}

void CommandHandler::handle(const std::string &cmd) {
    addCommand(cmd);
}
