#include "file_output.h"
#include <fstream>

using namespace std::chrono_literals;

FileOutput::FileOutput(OutputBuffer &buffer)
    : AOutputItem(buffer, "FileOutput")
{
}

void FileOutput::loop() {
    while (mWorking) {
        if (mBuffer.availableForProcessing()) {
            if (auto data = mBuffer.getProcessingData()) {
                auto value = data.value();
                std::fstream dumpFile;
                dumpFile.open(value.fileName, std::fstream::out | std::fstream::trunc);
                if (dumpFile.is_open()) {
#ifdef DEBUG
                    dumpFile << mProcessingThread.get_id() << " ";
#endif
                    for (auto item = value.data.cbegin(); item != value.data.cend(); ++item) {
                        if (item != value.data.cbegin()) {
                            dumpFile << ", ";
                        }
                        dumpFile << *item;
                    }
                    dumpFile << std::endl;
                    dumpFile.close();
                    incMetrics(value.data.size());
                }
            }
        }
        std::this_thread::sleep_for(50ms);
    }
}
