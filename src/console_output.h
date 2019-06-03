#pragma once
#include "output_item_abstract.h"

class ConsoleOutput : public AOutputItem
{
public:
    ConsoleOutput(OutputBuffer &buffer);
    void loop() override;
private:
    inline static std::mutex mOutputMutex;
};
