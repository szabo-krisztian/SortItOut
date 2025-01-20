#pragma once

#include "Algorithm.hpp"

namespace tlr
{
    
class SelectionSort final : public Algorithm
{
public:
    SelectionSort(volatile bool &isAppRunning) : Algorithm(isAppRunning) {}

    void Sort(SyncVector &numbers) override
    {
        for (std::size_t i = 0; i < numbers.size() - 1; ++i)
        {
            for (std::size_t j = i + 1; j < numbers.size(); ++j)
            {
                if (!m_isAppRunning) { return; }

                if (numbers[i] < numbers[j])
                {
                    numbers.Swap(i, j);
                }
            }
        }
    }
};

} // namespace tlr