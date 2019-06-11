#include "async_impl.h"
#include <sstream>

AsyncImpl::AsyncImpl(std::size_t bulk)
    : mBulk(bulk),
    mWorking(true)
{
    mTask = std::async(std::launch::async, &AsyncImpl::processData, this);
}

void AsyncImpl::disconnect() {
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

void AsyncImpl::receive(const std::string &data) {
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

void AsyncImpl::processData() {
    while (mWorking || !mPreparedData.empty()) {
        if (!mPreparedData.empty()) {
            std::lock_guard preparedDataLock(mPreparedDataMutex);
            mBulk << mPreparedData;
            mPreparedData.clear();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(50));
    }
}
