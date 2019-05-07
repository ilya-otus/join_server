#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <memory>
#include <bitset>
#include "bulk_interface.h"
#include "output_helper.h"


using BulkContainer = std::vector<std::string>;
class Bulk : public IBulk
{
public:
    Bulk(size_t bulkSize);
    ~Bulk();
    void addCommand(const std::string &cmd);
    void startOfBlock();
    void endOfBlock();
    void dumpAll();

private:
    std::vector<BulkContainer> mData;
    std::bitset<2> mStatus = 0;
    size_t mBulkSize;
    OutputHelper<> mOut;
};

