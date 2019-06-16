#pragma once
#include <functional>
#include <future>
#include <map>
#include <memory>
#include <queue>
#include <string>
#include <thread>
#include <unordered_map>
#include "parser.h"

class Handler;
class Storage
{
public:
    Storage(const Storage &) = delete;
    Storage& operator=(const Storage) = delete;
    ~Storage();
    Storage();
    void addCommand(int sessionId, const std::string &cmd, std::function<void(std::string)> callback);
    std::string insert(const std::string &tableName, int id, const std::string &name);
    std::string truncate(const std::string &tableName);
    std::string intersection() const;
    std::string symmetricDifference() const;
    void onSessionFinished(int sessionId);
private:
    std::string createTable(const std::string &tableName);
private:
    Parser mParser;
    std::map<std::string, std::map<int, std::string>> mTables;
    std::unordered_map<int, std::queue<std::future<void>>> mExecQueue;
    bool mWorking;
};
