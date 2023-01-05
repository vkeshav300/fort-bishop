#include <memory>

struct any
{
    void *data_;
    std::type_info const &type_;

    template <typename T>
    explicit any(T &&value) : data_(new T{std::forward<T>(value)}), type_(typeid(T))
    {
    }
};

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