#pragma once
#include <fstream>
#include <array>
#include <algorithm>
#include <type_traits>
#include <stack>

#include "console_output.h"
#include "file_output.h"

using namespace std::chrono_literals;
template<size_t PoolSize = 2, typename Log = ConsoleOutput, typename Dump = FileOutput>
class OutputHelper : public OutputItemConcept<Log>, public OutputItemConcept<Dump>
{
public:
    OutputHelper()
        : mLoggingItem(new Log(buf))
    {
        for (auto &dump : mDumpPool) {
            dump.reset(new Dump(buf));
        }
    };
    ~OutputHelper() {
        while (!buf.empty()) {
            std::this_thread::sleep_for(500ms);
        }
        mLoggingItem->stop();
        for (auto &dump : mDumpPool) {
            dump->stop();
        }
    }
    void operator<<(const std::vector<std::string> &o) {
        buf.append(o);
    }
private:
    std::array<std::unique_ptr<AOutputItem>, PoolSize> mDumpPool;
    OutputBuffer buf;
    std::unique_ptr<AOutputItem> mLoggingItem;
};

