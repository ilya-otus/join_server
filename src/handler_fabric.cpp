#include "handler_fabric.h"

std::shared_ptr<Handler> makeHandler(HandlerType type, std::shared_ptr<IBulk> bulk) {
    std::shared_ptr<Handler> pHandler(nullptr);
    if (type == HandlerType::Brace) {
        pHandler.reset(new BraceHandler(bulk));
    } else if (type == HandlerType::Command) {
        pHandler.reset(new CommandHandler(bulk));
    }
    return pHandler;
}
