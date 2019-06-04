#pragma once
#include "output_item_abstract.h"

class TestOutput : public AOutputItem
{
public:
    TestOutput(OutputBuffer &buffer)
        : AOutputItem(buffer, "TestOutput") 
    {
        init();
    }

    void loop() override {
        while (mWorking) {
            if (mBuffer.availableProcessedData()) {
                if (auto data = mBuffer.getProcessedData()) {
                    auto value = data.value();
                    mProcessedUnits.emplace_back(value);
                    incMetrics(value.data.size());
                }
            }
            std::this_thread::sleep_for(50ms);
        }
    }
    std::vector<ProcessingUnit> mProcessedUnits;
};
