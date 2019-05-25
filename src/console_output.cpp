#include "console_output.h"

using namespace std::chrono_literals;
ConsoleOutput::ConsoleOutput(OutputBuffer &buffer)
    : AOutputItem(buffer, "ConsoleOutput")
{
}

void ConsoleOutput::loop() {
    while (mWorking) {
        if (mBuffer.availableForOutput()) {
            if (auto data = mBuffer.getOutputData()) {
                auto value = data.value();
                std::cout << "bulk: ";
                for (auto item = value.cbegin(); item != value.cend(); ++item) {
                    if (item != value.cbegin()) {
                        std::cout << ", ";
                    }
                    std::cout << *item;
                }
                std::cout << std::endl;
                incMetrics(value.size());
            }
        }
        std::this_thread::sleep_for(50ms);
    }
    std::cout << std::endl;
}
