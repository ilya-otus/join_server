#pragma once
#include "output_item_abstract.h"

class TestOutput : public AOutputItem
{
public:
    TestOutput(OutputBuffer &buffer)
        : AOutputItem(buffer, "ConsoleOutput") { }

    void loop() override {
        while (mWorking) {
            if (mBuffer.availableProcessedData()) {
                if (auto data = mBuffer.getProcessedData()) {
                    mProcessingItems.emplace_back(data.value());
                    incMetrics(value.data.size());
                }
            }
            std::this_thread::sleep_for(50ms);
        }
    }
    std::vector<ProcessingItem> mProcessedItems;
};
