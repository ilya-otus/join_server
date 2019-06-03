#include "output_item_abstract.h"
#include <sstream>
#include <iostream>

AOutputItem::AOutputItem(OutputBuffer &buffer, const std::string &name)
    : mBuffer(buffer),
    mWorking(true), mCmdCount(0), mBlockCount(0),
    mName(name)
{
}

AOutputItem::~AOutputItem() {
    std::cout << "Thead " << mName
        << " (ID:" << mProcessingThreadId << "): "
        << mBlockCount << " blocks, "
        << mCmdCount << " commands" << std::endl;
}

void AOutputItem::stop() {
    mWorking = false;
    mProcessingThreadId = mProcessingThread.get_id();
    if (mProcessingThread.joinable()) {
        mProcessingThread.join();
    }
}

void AOutputItem::incMetrics(size_t cmdCount) {
    ++mBlockCount;
    mCmdCount += cmdCount;
}

void AOutputItem::init() {
    mProcessingThread = std::thread(&AOutputItem::loop, this);
}
