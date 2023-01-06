#pragma once

#include <memory>

struct any
{
    // Data
    void *data_;

    // The type the data is
    std::type_info const &type_;

    // Constructor
    template <typename T>
    explicit any(T &&value) : data_(new T{std::forward<T>(value)}), type_(typeid(T))
    {
    }
};

// Gets data from any object based on a specific type
template <typename T>
T &any_cast(any &any_)
{
    if (typeid(T) == any_.type_)
    {
        return *static_cast<T *>(any_.data_);
    }
    else
    {
        throw std::runtime_error("Error: any_cast(), invalid cast");
    }
}