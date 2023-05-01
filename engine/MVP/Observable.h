#include "Signal.h"

template<typename T>
class Observable
{
public:
    Observable(const T& value)
            : m_value(value)
    {}

    Observable(const Observable& observable)
            : m_value(observable.m_value)
    {}

    Observable& operator=(const T& value)
    {
        if (m_value == value)
            return *this;

        m_value = value;
        update();
        return *this;
    }

    Observable& operator=(const Observable& observable)
    {
        m_value = observable.m_value;
        update();
        return *this;
    }

    template<typename Callable>
    void connect(Callable callable)
    {
        m_signal.connect(callable);
    }

    operator T() const
    {
        return m_value;
    }

    Observable& operator++()
    {
        ++m_value;
        update();
        return *this;
    }

    Observable& operator--()
    {
        --m_value;
        update();
        return *this;
    }

    Observable& operator++(int)
    {
        m_value++;
        update();
        return *this;
    }

    Observable& operator--(int)
    {
        m_value--;
        update();
        return *this;
    }

    auto scopedBlock()
    {
        //return std::move(m_slotConnection.scopedBlock());
    }

private:
    void update()
    {
        m_signal.notify(m_value);
    }

    T m_value;
    Signal<T> m_signal;
    //slot_connection<T> m_slotConnection;
};
