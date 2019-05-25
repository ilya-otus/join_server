#include <vector>
#include <shared_mutex>
#include <optional>

struct ProcessingUnit {
    ProcessingUnit(const std::vector<std::string> &d)
        : data(d)
    {
    }
    std::vector<std::string> data;
    std::string fileName;
};

class OutputBuffer
{
public:
    void append(const std::vector<std::string> &data);
    std::optional<ProcessingUnit> getProcessingData();
    std::optional<std::vector<std::string>> getOutputData();
    bool availableForProcessing() const;
    bool availableForOutput() const;
    bool empty() const;
private:
    bool existsFileName(const std::string &fileName) const;
    std::string genFileName() const;
private:
    mutable std::shared_mutex mBufferMutex;
    std::vector<ProcessingUnit> mBuffer;
};
