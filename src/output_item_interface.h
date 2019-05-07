#pragma once

template <typename T, typename = void>
struct is_std_container : std::false_type { };

template <typename T>
struct is_std_container<T,
    std::void_t<decltype(std::declval<T&>().begin()),
           decltype(std::declval<T&>().end()),
           typename T::value_type>
    > : std::true_type { };

template <typename T>
inline constexpr bool is_std_container_v = is_std_container<T>::value;

template<typename T>
class IOutputItem
{
public:
    virtual ~IOutputItem() = default;
    bool available() const {
        return static_cast<const T*>(this)->isAvailable();
    }
    template<typename U>
    friend IOutputItem<T>& operator<<(IOutputItem<T> &outputItem, const U &value) {
        outputItem.dump(value);
        return outputItem;
    }
protected:
    template<typename U>
    void dump(const U &value) {
        static_cast<T*>(this)->output(value);
    }
};

