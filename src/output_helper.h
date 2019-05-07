#pragma once
#include <fstream>
#include <array>
#include <algorithm>

#include "console_output.h"
#include "file_output.h"

class string;

template<size_t poolSize = 3, typename Log = ConsoleOutput, typename Pool = FileOutput>
class OutputHelper
{
public:
    OutputHelper(bool loggingEnabled = true) : mLoggingEnabled(loggingEnabled) {};
    void operator<<(const std::vector<std::string> &o) {
        if (mLoggingEnabled) {
            mLoggingItem << o;
        }
        bool notFound = true;
        while (notFound) {
            for (auto &item : mProcessingPool) {
                if (item.available()) {
                    item << o;
                    notFound = false;
                    break;
                }
            }
        }
    }
    void setLoggingEnabled() {
        mLoggingEnabled = true;
    }
    void setLoggingDisabled() {
        mLoggingEnabled = false;
    }
private:
    std::array<Pool, poolSize> mProcessingPool;
    bool mLoggingEnabled;
    Log mLoggingItem;
};
