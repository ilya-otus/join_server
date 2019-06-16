#pragma once
#include "handler.h"

class SymmetricDifferenceHandler : public Handler
{
public:
    SymmetricDifferenceHandler(Storage *storage);
    std::string execute();
    static std::string commandName();
};
