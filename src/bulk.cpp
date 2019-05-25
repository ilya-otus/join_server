#include "bulk.h"

namespace Status {
const std::bitset<2> Started("01");
const std::bitset<2> Finished("10");
}

Bulk::Bulk(size_t bulkSize)
    : IBulk(),
    mBulkSize(bulkSize)
{
}

Bulk::~Bulk() {
    if (mData.back().size() != mBulkSize && mStatus == State::Undefined) {
        mOut << mData.back();
    }
}

void Bulk::addCommand(const std::string &c) {
    ++mCmdCount;
    if ((mData.size() == 0 || mData.back().size() == mBulkSize) && (mStatus != State::Started)) {
        mData.emplace_back(BulkContainer());
    }
    if (mStatus == State::Finished) {
        mData.emplace_back(BulkContainer());
        mStatus = State::Undefined;
    }
    mData.back().emplace_back(c);
    if (mData.back().size() == mBulkSize && (mStatus != State::Started)) {
        mOut << mData.back();
    }
}

void Bulk::startOfBlock() {
    mStatus = State::Started;
    if (mData.size() != 0 && mData.back().size() != mBulkSize) {
        mOut << mData.back();
    }
    mData.emplace_back(BulkContainer());
}

void Bulk::endOfBlock() {
    mStatus = State::Finished;
    mOut << mData.back();
}

Metrics Bulk::metrics() const {
    using namespace std::literals::string_literals;
    return {mData.size(), mCmdCount};
}

