#pragma once

#include <iostream>
#include <mutex>

namespace utils {

    template<typename T>
    class Singleton
    {
    private:
        static T* m_pInstance;
        static std::once_flag m_onceFlag;

    protected:
        Singleton() {}

    public:
        virtual ~Singleton()
        {
            delete m_pInstance;
            m_pInstance = nullptr;
        }

        static T* GetInstance()
        {
            std::call_once(m_onceFlag, []()
                {
                    m_pInstance = new T;
                });

            return m_pInstance;
        }

        Singleton(const Singleton&) = delete;
        Singleton(Singleton&&) = delete;
        Singleton& operator=(const Singleton&) = delete;
        Singleton& operator=(Singleton&&) = delete;
    };

    template<typename T>
    T* Singleton<T>::m_pInstance = nullptr;

    template<typename T>
    std::once_flag Singleton<T>::m_onceFlag;

}