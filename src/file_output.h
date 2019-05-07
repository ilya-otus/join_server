#pragma once
#include <fstream>
#include <type_traits>
#include "output_item_interface.h"

class FileOutput : public IOutputItem<FileOutput>
{
public:
    ~FileOutput();
    template<typename T>
    typename std::enable_if_t<is_std_container_v<T>, void>
    output(const T &value) {
        if (init()) {
            mDumpFile << "bulk: ";
            for (auto item = value.begin(); item != value.end(); ++item) {
                mDumpFile << *item;
                if (item != value.end()-1) {
                    mDumpFile << ", ";
                }
            }
            mDumpFile << std::endl;
            mInitialized = false;
            mDumpFile.close();
        }
    }

    bool isAvailable() const;
private:
    std::string genFileName() const;
    bool init();
private:
    bool mInitialized = false;
    std::fstream mDumpFile;
    inline static size_t suffixCounter = 0;
};
