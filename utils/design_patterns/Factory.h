#pragma once
#include "Typelist.h"
#include <memory>


template<typename ValidTypes, template<class...> class SmartPtrType = std::unique_ptr>
class Factory
{
public:

    template<typename T>
    using SmartPtr = SmartPtrType<T>;

    template<typename Type, typename... Args>
    static SmartPtr<Type> create(Args... args)
    {
        return SmartPtr<typename Creator<Type>::type>(
            new typename Creator<Type>::type(args...));
    };

private:
    template<typename Type>
    struct Creator
    {
        static_assert(contains_v<ValidTypes, Type>);
        using type = Type;
    };
};