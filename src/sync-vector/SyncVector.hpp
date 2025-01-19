#pragma once

#include <iostream>
#include <vector>
#include <mutex>

namespace tlr
{
    
class SyncVector
{
public:
    SyncVector(std::size_t size);

    void Swap(std::size_t i, std::size_t j);
    void Lock();
    void Unlock();
    int operator[](std::size_t i) const;
    void Shuffle();
    std::size_t size() const;

    friend std::ostream& operator<<(std::ostream &os, const SyncVector &obj);

private:
    std::vector<int> m_numbers;
    std::mutex m_mutex;
};

std::ostream& operator<<(std::ostream &os, const SyncVector &obj);

} // namespace tlr

