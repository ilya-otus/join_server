#include "async.h"
#include "async_impl.h"
#include <memory>
#include <iostream>

namespace async {

class Async {
public:
    Async(std::size_t bulk) : pImpl(new AsyncImpl(bulk)) { }
    ~Async() = default;
    void receive(const std::string& data) {
        pImpl->receive(data);
    }
    void disconnect() {
        pImpl->disconnect();
    }
private:
    std::unique_ptr<AsyncImpl> pImpl;
};

handle_t connect(std::size_t bulk) {
    return new Async(bulk);
}

void receive(handle_t handle, const char *data, std::size_t size) {
    handle->receive({data, size});
}

void disconnect(handle_t handle) {
    handle->disconnect();
    delete handle;
}

}
