#include "handler.h"

Handler::Handler(std::shared_ptr<IBulk> bulk)
    : mNext(nullptr),
    mBulk(bulk)
{ }

void Handler::setNext(std::shared_ptr<Handler> next) {
    mNext = next;
}

void Handler::add(std::shared_ptr<Handler> next) {
    if (mNext != nullptr) {
        mNext->add(next);
    } else {
        mNext = next;
    }
}

void Handler::handle(const std::string &cmd) {
    mNext->handle(cmd);
}

void Handler::startOfBlock() {
    if (mBulk != nullptr) {
        mBulk->startOfBlock();
    }
}

void Handler::endOfBlock() {
    if (mBulk != nullptr) {
        mBulk->endOfBlock();
    }
}

void Handler::addCommand(const std::string &cmd) {
    if (mBulk != nullptr) {
        mBulk->addCommand(cmd);
    }
}
