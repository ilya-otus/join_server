#pragma once
#include <iostream>
#include <type_traits>
#include "output_item_abstract.h"

class ConsoleOutput : public AOutputItem
{
public:
    ConsoleOutput(OutputBuffer &buffer);
    void loop() override;
};
