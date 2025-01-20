#pragma once

#include "SyncVector.hpp"

namespace tlr
{
    
class Algorithm
{
public:
    Algorithm(volatile bool &isAppRunning) : m_isAppRunning(isAppRunning) {}
    virtual ~Algorithm() = default;    

    virtual void Sort(SyncVector &numbers) = 0;

protected:
    volatile bool &m_isAppRunning;
};

} // namespace tlr