#pragma once
#include "handler.h"

class BraceHandler : public Handler
{
public:
    BraceHandler(std::shared_ptr<IBulk> bulk);
    void handle(const std::string &cmd) final;
private:
    int openCount = 0;
};

