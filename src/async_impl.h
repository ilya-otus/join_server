#pragma once
#include "bulk_proxy.h"
#include <future>
#include <queue>
#include <sstream>

class AsyncImpl {
public:
    AsyncImpl(std::size_t bulk) : mBulk(bulk), mWorking(true) {
        mTask = std::async(std::launch::async, &AsyncImpl::processData, this);
    }
    ~AsyncImpl() { }
    void disconnect() {
        if (!mUnfinishedCache.empty()) {
            std::stringstream ss;
            ss << mUnfinishedCache;
            std::lock_guard preparedDataLock(mPreparedDataMutex);
            for (std::string cmd; std::getline(ss, cmd); ) {
                mPreparedData.emplace_back(cmd);
            }
        }
        mWorking = false;
        if (mTask.valid()) {
            mTask.wait();
        }
    }
    void receive(const std::string &data) {
        bool isFinished = (data.back() == '\n');
        std::stringstream ss;
        ss << mUnfinishedCache;
        ss << data;
        mUnfinishedCache.clear();
        std::lock_guard preparedDataLock(mPreparedDataMutex);
        for (std::string cmd; std::getline(ss, cmd); ) {
            mPreparedData.emplace_back(cmd);
        }
        if (!isFinished && !mPreparedData.empty()) {
            mUnfinishedCache = mPreparedData.back();
            mPreparedData.pop_back();
        }
    }
private:
    void processData() {
        while (mWorking || !mPreparedData.empty()) {
            if (!mPreparedData.empty()) {
                std::lock_guard preparedDataLock(mPreparedDataMutex);
                mBulk << mPreparedData;
                mPreparedData.clear();
            }
            std::this_thread::sleep_for(std::chrono::milliseconds(50));
        }
    }
private:
    BulkProxy mBulk;
    std::future<void> mTask;
    std::string mUnfinishedCache;
    std::vector<std::string> mPreparedData;
    std::mutex mPreparedDataMutex;
    bool mWorking;
};
