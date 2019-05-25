#pragma once
#include "output_item_abstract.h"

class FileOutput : public AOutputItem
{
public:
    FileOutput(OutputBuffer &buffer);
    void loop();
};
