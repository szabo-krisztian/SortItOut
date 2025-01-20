#include "SyncVector.hpp"

#include <numeric>
#include <algorithm>
#include <random>

namespace tlr
{

SyncVector::SyncVector(std::size_t size, long long swapTimeInMillis) :
    m_numbers(size),
    m_swapTimeInMillis(swapTimeInMillis)
{
    std::iota(m_numbers.begin(), m_numbers.end(), 1);
    Shuffle();
}

void SyncVector::Swap(std::size_t i, std::size_t j)
{
    {
        std::lock_guard<std::mutex> lk(m_mutex);
        std::swap(m_numbers[i], m_numbers[j]);
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(m_swapTimeInMillis));
}

void SyncVector::Assign(std::size_t i, int value)
{
    {
        std::lock_guard<std::mutex> lk(m_mutex);
        m_numbers[i] = value;
    }
    std::this_thread::sleep_for(std::chrono::milliseconds(m_swapTimeInMillis));
}

void SyncVector::Lock()
{
    m_mutex.lock();
}

void SyncVector::Unlock()
{
    m_mutex.unlock();
}

int SyncVector::operator[](std::size_t i) const
{
    return m_numbers[i];
}

void SyncVector::Shuffle()
{
    static std::random_device randomDevice;
    static std::mt19937 generator(randomDevice());
    std::shuffle(m_numbers.begin(), m_numbers.end(), generator);
}

std::size_t SyncVector::size() const
{
    return m_numbers.size();
}

std::ostream& operator<<(std::ostream &os, const tlr::SyncVector &obj)
{
    for (auto &x : obj.m_numbers)
    {
        os << x << " ";
    }
    return os;
}

} // namespace tlr