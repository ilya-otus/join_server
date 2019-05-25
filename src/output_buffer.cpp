#include "output_buffer.h"
#include <filesystem>
#include <algorithm>
#include <mutex>

namespace {
using namespace std::string_literals;
const auto prefix = "bulk"s;
const auto extension = ".log"s;
const auto delimiter = "_"s;

auto notProcessedPredicate = [] (const ProcessingUnit &unit) {
    return unit.fileName.empty();
};
auto processedPredicate = [] (const ProcessingUnit &unit) {
    return !unit.fileName.empty();
};

} // namespace

void OutputBuffer::append(const std::vector<std::string> &data) {
    std::unique_lock lock(mBufferMutex);
    mBuffer.emplace_back(data);
}

std::optional<ProcessingUnit> OutputBuffer::getProcessingData() {
    std::unique_lock lock(mBufferMutex);
    auto unit = std::find_if(mBuffer.begin(), mBuffer.end(), notProcessedPredicate);
    if (unit == mBuffer.end()) {
        return {};
    }
    unit->fileName = genFileName();
    return {*unit};
}

std::optional<std::vector<std::string>> OutputBuffer::getOutputData() {
    std::unique_lock lock(mBufferMutex);
    auto unit = std::find_if(mBuffer.begin(), mBuffer.end(), processedPredicate);
    if (unit == mBuffer.end()) {
        return {};
    }
    auto result(unit->data);
    mBuffer.erase(unit);
    return result;
}

bool OutputBuffer::availableForProcessing() const {
    std::shared_lock lock(mBufferMutex);
    return std::any_of(mBuffer.begin(), mBuffer.end(), notProcessedPredicate);
}

bool OutputBuffer::availableForOutput() const {
    std::shared_lock lock(mBufferMutex);
    return std::any_of(mBuffer.begin(), mBuffer.end(), processedPredicate);
}

bool OutputBuffer::empty() const {
    std::shared_lock lock(mBufferMutex);
    return mBuffer.empty();
}

bool OutputBuffer::existsFileName(const std::string &fileName) const {
    return std::any_of(mBuffer.begin(), mBuffer.end(), [&fileName] (const ProcessingUnit &item) { return fileName == item.fileName; });
}

std::string OutputBuffer::genFileName() const {
    std::string fileName(prefix);
    fileName += std::to_string(std::time(nullptr));
    std::string suffix;
    size_t suffixCounter = 0;
    for (auto name = fileName + suffix + extension;
         std::filesystem::exists(std::filesystem::path(name)) || existsFileName(name);
         name = fileName + suffix + extension) {
        suffix = delimiter + std::to_string(suffixCounter++);
    }
    fileName += suffix + extension;
    return fileName;
}

