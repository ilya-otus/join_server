#pragma once
#include "handler.h"

class CommandHandler : public Handler
{
public:
    CommandHandler(std::shared_ptr<IBulk> bulk);
    void handle(const std::string &cmd) final;
};
