#include "brace_handler.h"

BraceHandler::BraceHandler(std::shared_ptr<IBulk> bulk)
    : Handler(bulk)
{ }

void BraceHandler::handle(const std::string &cmd) {
    if (cmd == "{") {
        if (openCount++ == 0) {
            startOfBlock();
        }
    } else if (cmd == "}") {
        if (--openCount == 0) {
            endOfBlock();
        }
    } else {
        Handler::handle(cmd);
    }
}
