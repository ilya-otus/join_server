#include "storage.h"
#include "handler.h"
#include <iostream>

using namespace std::chrono_literals;
using namespace std::string_literals;

Storage::Storage()
    : mParser(this),
    mWorking(true)
{
    createTable("A"s);
    createTable("B"s);
}

Storage::~Storage() = default;

void Storage::onSessionFinished(int sessionId) {
    auto &sessionQueue = mExecQueue[sessionId];
    while(!sessionQueue.empty()) {
        if (sessionQueue.front().valid()) {
            sessionQueue.front().wait();
        }
        sessionQueue.pop();
    }
}

void Storage::addCommand(int sessionId, const std::string &cmd, std::function<void(std::string)> callback) {
    auto handler = mParser.parse(cmd);
    if (handler == nullptr) {
        callback("ERR undefined command"s);
        return;
    }
    mExecQueue[sessionId].push(std::async(std::launch::async, &Handler::handle, std::move(handler), callback));
}

std::string Storage::insert(const std::string &tableName, int id, const std::string &name) {
    if (mTables.count(tableName) == 0) {
        return "ERR table not exists"s;
    }
    auto table = mTables.find(tableName);
    if (table->second.count(id) != 0) {
        return "ERR duplicate"s;
    }
    if (auto record = table->second.insert({id, name}); !record.second) {
        return "ERR insert"s;
    }
    return "OK"s;
}

std::string Storage::truncate(const std::string &tableName) {
    if (mTables.count(tableName) == 0) {
        return "ERR table not exists"s;
    }
    mTables.at(tableName).clear();
    return "OK"s;
}

std::string Storage::intersection() const {
    auto tableA = mTables.find("A"s);
    auto tableB = mTables.find("B"s);
    if (tableA == mTables.end() || tableB == mTables.end()) {
        return "ERR table not exists"s;
    }
    std::vector<std::pair<int, std::string>> out;
    std::set_intersection(tableA->second.begin(), tableA->second.end(),
                          tableB->second.begin(), tableB->second.end(),
                          std::back_inserter(out), [] (auto f, auto s) { return f.first < s.first; });
    std::string response;
    for (const auto &o : out) {
        response += std::to_string(o.first);
        response += ", ";
        response += tableA->second.at(o.first);
        response += ", ";
        response += tableB->second.at(o.first);
        response += '\n';
    }
    return response + "OK"s;
}

std::string Storage::symmetricDifference() const {
    auto tableA = mTables.find("A"s);
    auto tableB = mTables.find("B"s);
    if (tableA == mTables.end() || tableB == mTables.end()) {
        return "ERR table not exists"s;
    }
    std::vector<std::pair<int, std::string>> out;
    std::set_symmetric_difference(tableA->second.begin(), tableA->second.end(),
                                  tableB->second.begin(), tableB->second.end(),
                                  std::back_inserter(out), [] (auto f, auto s) { return f.first < s.first; });
    std::string response;
    for (const auto &o : out) {
        response += std::to_string(o.first);
        response += ", ";
        if (tableA->second.count(o.first) > 0) {
            response += tableA->second.at(o.first);
        }
        response += ", ";
        if (tableB->second.count(o.first) > 0) {
            response += tableB->second.at(o.first);
        }
        response += '\n';
    }
    return response + "OK"s;
}

std::string Storage::createTable(const std::string &tableName) {
    if (auto table = mTables.find(tableName); table == mTables.end()) {
        auto createTable = mTables.insert({tableName, {}});
        if (!createTable.second) {
            return "ERR create table"s;
        }
        table = createTable.first;
    }
    return "OK"s;
}
