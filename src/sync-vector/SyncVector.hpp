#pragma once

#include <iostream>
#include <vector>
#include <mutex>

namespace tlr
{
    
class SyncVector
{
public:
    SyncVector(std::size_t size, long long swapTimeInMillis);

    void Swap(std::size_t i, std::size_t j);
    void Assign(std::size_t i, int value);
    void Lock();
    void Unlock();
    int operator[](std::size_t i) const;
    void Shuffle();
    std::size_t size() const;

    friend std::ostream& operator<<(std::ostream &os, const SyncVector &obj);

private:
    std::vector<int> m_numbers;
    std::mutex m_mutex;
    long long m_swapTimeInMillis;
};

std::ostream& operator<<(std::ostream &os, const SyncVector &obj);

} // namespace tlr

