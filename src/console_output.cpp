#include "console_output.h"
#include <iostream>

using namespace std::chrono_literals;
ConsoleOutput::ConsoleOutput(OutputBuffer &buffer)
    : AOutputItem(buffer, "ConsoleOutput")
{
}

void ConsoleOutput::loop() {
    while (mWorking) {
        if (mBuffer.availableProcessedData()) {
            if (auto data = mBuffer.getProcessedData()) {
                auto value = data.value();
                std::cout << "bulk: ";
                for (auto item = value.data.cbegin(); item != value.data.cend(); ++item) {
                    if (item != value.data.cbegin()) {
                        std::cout << ", ";
                    }
                    std::cout << *item;
                }
                std::cout << std::endl;
                incMetrics(value.data.size());
            }
        }
        std::this_thread::sleep_for(50ms);
    }
    std::cout << std::endl;
}
