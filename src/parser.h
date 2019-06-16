#pragma once
#include <string>
#include <memory>

class Handler;
class Storage;
class Parser {
public:
    Parser(Storage *storage);
    std::unique_ptr<Handler> parse(const std::string &command) const;
private:
    Storage *mStorage;
};
