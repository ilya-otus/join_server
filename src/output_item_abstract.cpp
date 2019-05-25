#include "output_item_abstract.h"

AOutputItem::AOutputItem(OutputBuffer &buffer)
    : mBuffer(buffer),
    mProcessingThread(&AOutputItem::loop, this),
    mWorking(true)
{
}

AOutputItem::~AOutputItem() {
    mProcessingThread.join();
}

void AOutputItem::stop() {
    mWorking = false;
}
