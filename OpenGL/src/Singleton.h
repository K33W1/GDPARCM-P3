#pragma once
#include <type_traits>

template<typename T>
class Singleton
{
protected:
    Singleton() noexcept = default;
    Singleton(const Singleton&) = delete;
    Singleton& operator=(const Singleton&) = delete;
    virtual ~Singleton() = default;

public:
    static T& getInstance() noexcept(std::is_nothrow_constructible<T>::value)
    {
        static T instance;
        return instance;
    }
};
