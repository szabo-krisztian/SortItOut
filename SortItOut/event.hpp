#pragma once

#include <vector>
#include <functional>

namespace tlr
{

template<typename R, typename... Args>
class Event
{
public:
    template<typename F>
    void operator+=(F&& listener)
    {
        _listeners.emplace_back(std::forward<F>(listener));
    }

    void Raise(Args... args)
    {
        for (const auto& listener : _listeners)
        {
            listener(std::forward<Args...>(args)...);
        }
    }

private:
    std::vector<std::function<R(Args...)>> _listeners;
};

} // namespace tlr