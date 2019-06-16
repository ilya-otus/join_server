#pragma once
#include "handler.h"

class IntersectionHandler : public Handler
{
public:
    IntersectionHandler(Storage *storage);
    std::string execute();
    static std::string commandName();
};
