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

ProcessingUnit::ProcessingUnit(const std::vector<std::string> &d)
    : data(d), fileName("")
{
}

ProcessingUnit::ProcessingUnit(const ProcessingUnit &other)
    : data(other.data),
    fileName(other.fileName)
{
}

ProcessingUnit& ProcessingUnit::operator=(const ProcessingUnit &other) {
    data = other.data;
    fileName = other.fileName;
    return *this;
}

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
    std::lock_guard lockFileScope(mFileScopeMutex);
    unit->fileName = genFileName();
    mFileScope.emplace_back(unit->fileName);
    return {*unit};
}

std::optional<ProcessingUnit> OutputBuffer::getProcessedData() {
    std::unique_lock lock(mBufferMutex);
    auto unit = std::find_if(mBuffer.begin(), mBuffer.end(), processedPredicate);
    if (unit == mBuffer.end()) {
        return {};
    }
    auto result(*unit);
    mBuffer.erase(unit);
    return result;
}

bool OutputBuffer::availableForProcessing() const {
    std::shared_lock lock(mBufferMutex);
    return std::any_of(mBuffer.begin(), mBuffer.end(), notProcessedPredicate);
}

bool OutputBuffer::availableProcessedData() const {
    std::shared_lock lock(mBufferMutex);
    return std::any_of(mBuffer.begin(), mBuffer.end(), processedPredicate);
}

bool OutputBuffer::empty() const {
    std::shared_lock lock(mBufferMutex);
    return mBuffer.empty();
}

bool OutputBuffer::existsFileName(const std::string &fileName) const {
    auto fileNamePredicate = [fileName] (const std::string &item) { return fileName == item; };
    return std::any_of(mFileScope.begin(), mFileScope.end(), fileNamePredicate);
}

std::string OutputBuffer::genFileName() const {
    std::string fileName(prefix);
    fileName += std::to_string(std::time(nullptr));
    std::string suffix;
    size_t suffixCounter = 0;
    for (auto name = fileName + suffix + extension;
         existsFileName(name);
         name = fileName + suffix + extension) {
        suffix = delimiter + std::to_string(suffixCounter++);
    }
    fileName += suffix + extension;
    return fileName;
}

