#pragma once

#include <functional>
#include <stdexcept>
#include <variant>

namespace utils
{
    template<typename... Types>
    struct overload : Types...
    {
        using Types::operator()...;
    };

    template<class... Types>
    overload(Types...) -> overload<Types...>;

    template<typename Variant, typename... Matchers>
    void checkState(Variant& variant, Matchers&&... matchers)
    {
        std::visit(overload{ std::forward<Matchers>(matchers)... },
                   variant);
    }
}


template<typename... Args>
struct connection
{
    using fn_type = std::function<void(Args...)>;
    struct managed {};
    struct scoped {};
    struct zombified {};

    using state_type = std::variant<managed, scoped, zombified>;

    connection(fn_type _fn, state_type _state, Signal<Args...>* _signal)
            : fn(_fn), state(_state), signal(_signal) {}

    fn_type fn;
    state_type state;
    Signal<Args...>* signal;
};

template<typename... Args>
struct scoped_connection
{
    friend Signal<Args...>;
    scoped_connection();
    scoped_connection(const scoped_connection&) = default;
    scoped_connection(scoped_connection&& scopedConnection);
    scoped_connection& operator=(const scoped_connection&) = default;
    scoped_connection& operator=(scoped_connection&& scopedConnection);
    ~scoped_connection();

private:
    using connection_type = connection<Args...>;
    using connection_type_ptr = connection_type*;

    explicit scoped_connection(connection_type_ptr pConnection);
    void disconnect() const;

    mutable connection_type_ptr m_connection;
};

struct semaphore
{
    semaphore() : m_counter(0) {}

    void addBlocker() { ++m_counter; }
    void removeBlocker() { --m_counter; }
    bool isDisabled() const { return m_counter == 0; }

private:
    size_t m_counter;
};

template<typename... Args>
struct slot_connection
{
    slot_connection(Signal<Args...>& signal,
                    const typename Signal<Args...>::FnType& fn);

    void block();
    void unblock();
    auto scopedBlock();

    slot_connection(const slot_connection<Args...>& oth) = delete;
    slot_connection(slot_connection<Args...>&& oth) = delete;
    slot_connection& operator=(const slot_connection<Args...>& oth) = delete;
    slot_connection& operator=(slot_connection<Args...>&& oth) = delete;

private:
    scoped_connection<Args...> m_scopedConnection;
    semaphore m_blockSemaphore;
};

template<typename... Args>
scoped_connection<Args...>::scoped_connection()
        : m_connection(nullptr)
{
}

template<typename... Args>
scoped_connection<Args...>::scoped_connection(
        scoped_connection<Args...>&& scopedConnection)
{
    std::swap(m_connection, scopedConnection.m_connection);
}

template<typename... Args>
scoped_connection<Args...>& scoped_connection<Args...>::operator=(
        scoped_connection<Args...>&& scopedConnection)
{
    std::swap(m_connection, scopedConnection.m_connection);
    return *this;
}

template<typename... Args>
scoped_connection<Args...>::~scoped_connection()
{
    disconnect();
}

template<typename... Args>
void scoped_connection<Args...>::disconnect() const
{
    if (m_connection)
        m_connection->signal->disconnect(m_connection);
}

template<typename... Args>
scoped_connection<Args...>::scoped_connection(connection_type_ptr pConnection)
        : m_connection(pConnection)
{}

template<typename... Args>
slot_connection<Args...>::slot_connection(Signal<Args...>& signal,
                                          const typename Signal<Args...>::FnType& fn)
        : m_scopedConnection(signal.connectScoped([=](Args... args)
                                                  {
                                                      if (!m_blockSemaphore.isDisabled())
                                                          return;

                                                      fn(args...);
                                                  }))
        , m_blockSemaphore{}
{}

template <typename ... Args>
void slot_connection<Args...>::block()
{
    m_blockSemaphore.addBlocker();
}

template <typename ... Args>
void slot_connection<Args...>::unblock()
{
    m_blockSemaphore.removeBlocker();
}

template <typename ... Args>
auto slot_connection<Args...>::scopedBlock()
{
    struct BlockScoped
    {
        explicit BlockScoped(slot_connection<Args...>& owner)
                : m_owner(owner)
        {
            m_owner.block();
        }

        ~BlockScoped()
        {
            m_owner.unblock();
        }

        slot_connection<Args...>& m_owner;
    };

    return BlockScoped{ *this };
}

template<typename... Args>
struct Signal
{
public:
    using ConnectionType = connection<Args...>;
    using ConnectionTypePtr = ConnectionType*;
    using FnType = typename ConnectionType::fn_type;
    using ScopedConnectionType = scoped_connection<Args...>;
    using SlotConnectionType = slot_connection<Args...>;

    Signal() = default;
    ~Signal();
    void connect(const FnType& fn) const;

    template<typename Type>
    void connect(Type* instance, void (Type::* fn)(Args...)) const;

    template<typename Type>
    void connect(Type* instance, void (Type::* fn)(Args...) const) const;

    ScopedConnectionType connectScoped(const FnType& fn);
    SlotConnectionType connectSlot(const FnType& fn);

    void disconnect(ConnectionTypePtr& connection) const;
    void notify(const Args&... args);

private:
    mutable std::vector<ConnectionTypePtr> m_connections;
};

template<typename... Args>
void Signal<Args...>::connect(const FnType& fn) const
{
    auto* connection = new ConnectionType(fn,
                                          typename ConnectionType::state_type{
                                                  typename ConnectionType::managed{}
                                          },
                                          const_cast<Signal<Args...>*>(this));
    m_connections.push_back(connection);
}

template<typename... Args>
template<typename Type>
void Signal<Args...>::connect(Type* instance, void (Type::* fn)(Args...)) const
{
    auto func = [instance, fn](Args... args) { (instance->*fn)(args...); };

    auto* connection = new ConnectionType(func,
                                          typename ConnectionType::state_type{
                                                  typename ConnectionType::managed{}
                                          },
                                          const_cast<Signal<Args...>*>(this));
    m_connections.push_back(connection);
}

template<typename... Args>
template<typename Type>
void Signal<Args...>::connect(Type* instance, void (Type::* fn)(Args...) const) const
{
    auto func = [instance, fn](Args... args) { (instance->*fn)(args...); };

    auto* connection = new ConnectionType(func,
                                          typename ConnectionType::state_type{
                                                  typename ConnectionType::managed{}
                                          },
                                          const_cast<Signal<Args...>*>(this));
    m_connections.push_back(connection);
}

template<typename... Args>
void Signal<Args...>::notify(const Args&... args)
{
    auto connections = m_connections;
    for (auto& connection : connections)
        connection->fn(args...);
}

template<typename... Args>
Signal<Args...>::~Signal()
{
    for (auto& connection : m_connections)
    {
        utils::checkState(connection->state,
                          [&](typename ConnectionType::managed)->void
                          {
                              delete connection;
                          },
                          [&](typename ConnectionType::scoped)->void
                          {
                              connection->state = typename ConnectionType::zombified{};
                          },
                          [&](typename ConnectionType::zombified)->void
                          {
                              delete connection;
                          }
        );
    }
}

template<typename... Args>
void Signal<Args...>::disconnect(ConnectionTypePtr& connection) const
{
    auto it = std::find_if(m_connections.begin(), m_connections.end(),
                           [&](ConnectionTypePtr pConnection)
                           {
                               return pConnection == connection;
                           });

    if (it == m_connections.end())
        throw std::runtime_error("Connection is not attached to the signal");

    utils::checkState(connection->state,
                      [&](typename ConnectionType::managed)->void
                      {
                          throw std::runtime_error("Connection is managed typed");
                      },
                      [&](typename ConnectionType::scoped)->void
                      {
                          m_connections.erase(it);
                      },
                      [&](typename ConnectionType::zombified)->void
                      {
                      }
    );

    delete connection;
    connection = nullptr;
}

template<typename... Args>
typename Signal<Args...>::ScopedConnectionType
Signal<Args...>::connectScoped(const typename Signal<Args...>::FnType& fn)
{
    auto* connection = new ConnectionType(fn,
                                          typename ConnectionType::state_type{
                                                  typename ConnectionType::scoped{}
                                          }, this);
    m_connections.push_back(connection);
    return ScopedConnectionType{ connection };
}

template <typename ... Args>
typename Signal<Args...>::SlotConnectionType
Signal<Args...>::connectSlot(const FnType& fn)
{
    return SlotConnectionType(*this, fn);
}

