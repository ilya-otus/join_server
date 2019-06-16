#pragma once
#include "handler.h"

class TruncateHandler : public Handler
{
public:
    TruncateHandler(Storage *storage);
    std::string execute();
    static std::string commandName();
};
