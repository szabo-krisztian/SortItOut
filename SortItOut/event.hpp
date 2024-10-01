#pragma once

#include <unordered_set>

namespace tlr
{

template<typename R, typename... Args>
class Event
{
public:
    void operator+=(R(*listener)(Args...))
    {
        _listeners.insert(listener);
    }

    void operator-=(R(*listener)(Args...))
    {
        _listeners.erase(listener);
    }

    void Raise(Args... args)
    {
        for (const auto& listener : _listeners)
        {
            listener(std::forward<Args...>(args)...);
        }
    }

private:
    std::unordered_set<R(*)(Args...)> _listeners;
};

} // namespace tlr