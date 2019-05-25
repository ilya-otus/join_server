#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <bitset>
#include "bulk_interface.h"
#include "output_helper.h"

enum class State {
    Started,
    Finished,
    Undefined
};

using BulkContainer = std::vector<std::string>;
class Bulk : public IBulk
{
public:
    Bulk(size_t bulkSize);
    ~Bulk();
    void addCommand(const std::string &cmd);
    void startOfBlock();
    void endOfBlock();
    Metrics metrics() const override;
private:
    std::vector<BulkContainer> mData;
    State mStatus = State::Undefined;
    size_t mBulkSize;
    OutputHelper<> mOut;
    size_t mCmdCount = 0;
};

