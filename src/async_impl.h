#pragma once
#include "bulk_proxy.h"
#include <future>

class AsyncImpl {
public:
    AsyncImpl(std::size_t bulk);
    ~AsyncImpl() = default;
    void disconnect();
    void receive(const std::string &data);
private:
    void processData();
private:
    BulkProxy mBulk;
    std::future<void> mTask;
    std::string mUnfinishedCache;
    std::vector<std::string> mPreparedData;
    std::mutex mPreparedDataMutex;
    bool mWorking;
};
