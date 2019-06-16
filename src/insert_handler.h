#pragma once
#include "handler.h"

class InsertHandler : public Handler
{
public:
    InsertHandler(Storage *storage);
    std::string execute();
    static std::string commandName();
};
