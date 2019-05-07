#pragma once
#include <iostream>
#include <type_traits>
#include "output_item_interface.h"

class ConsoleOutput : public IOutputItem<ConsoleOutput>
{
public:
    template<typename T>
    typename std::enable_if_t<
            is_std_container_v<T>, void
            > output(const T &value) {
        std::cout << "bulk: ";
        for (auto item = value.begin(); item != value.end(); ++item) {
            std::cout << *item;
            if (item != value.end()-1) {
                std::cout << ", ";
            }
        }
        std::cout << std::endl;
    }
    bool isAvailable() const;
};
