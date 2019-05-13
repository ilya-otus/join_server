#pragma once
#include <fstream>
#include <array>
#include <algorithm>
#include <type_traits>

#include "console_output.h"
#include "file_output.h"

template<size_t PoolSize = 2, typename Log = ConsoleOutput, typename Pool = FileOutput>
class OutputHelper : public OutputItemConcept<Log>, public OutputItemConcept<Pool>
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
    std::array<Pool, PoolSize> mProcessingPool;
    bool mLoggingEnabled;
    Log mLoggingItem;
};
