#include "file_output.h"
#include <ctime>
#include <filesystem>

using namespace std::string_literals;
const auto prefix = "bulk"s;
const auto extension = ".log"s;

FileOutput::~FileOutput() {
    if (mInitialized) {
        mDumpFile.close();
    }
}

bool FileOutput::isAvailable() const {
    return !mInitialized;
}

bool FileOutput::init() {
    if (!mInitialized) {
        auto fileName = genFileName();
        mDumpFile.open(fileName, std::fstream::out | std::fstream::trunc);
        mInitialized = mDumpFile.is_open();
    }
    return mInitialized;
}

std::string FileOutput::genFileName() const {
    std::string fileName(prefix);
    fileName += std::to_string(std::time(nullptr));
    std::string suffix;
    if (suffixCounter != 0) {
        suffix = ""s + std::to_string(suffixCounter);
    }
    while (std::filesystem::exists(std::filesystem::path(fileName + suffix + extension))) {
        suffix = ""s + std::to_string(++suffixCounter);
    }
    fileName += suffix + extension;
    return fileName;
}
