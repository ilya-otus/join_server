#include "output_item_abstract.h"
#include <sstream>
#include <iostream>

AOutputItem::AOutputItem(OutputBuffer &buffer, const std::string &name)
    : mBuffer(buffer),
    mProcessingThread(&AOutputItem::loop, this),
    mWorking(true), mCmdCount(0), mBlockCount(0),
    mName(name)
{
}

AOutputItem::~AOutputItem() {
    auto id = mProcessingThread.get_id();
    mProcessingThread.join();
    std::cout << "Thead " << mName
        << " (ID:" << id << "): "
        << mBlockCount << " blocks, "
        << mCmdCount << " commands" << std::endl;
}

void AOutputItem::stop() {
    mWorking = false;
}

void AOutputItem::incMetrics(size_t cmdCount) {
    ++mBlockCount;
    mCmdCount += cmdCount;
}
