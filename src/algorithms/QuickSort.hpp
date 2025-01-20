#pragma once

#include "Algorithm.hpp"

namespace tlr
{
    
class QuickSort final : public Algorithm
{
public:
    QuickSort(volatile bool &isAppRunning) : Algorithm(isAppRunning) {}

    void Sort(SyncVector &numbers) override
    {
        QuickSort_(numbers, 0, static_cast<int>(numbers.size() - 1));
    }

private:
    int Partition(SyncVector &numbers, int low, int high)
    {
        int pivot = numbers[high];
        int i = low - 1;

        for (int j = low; j < high; ++j)
        {
            if (numbers[j] <= pivot)
            {
                ++i;
                numbers.Swap(i, j);
            }
        }

        numbers.Swap(i + 1, high);

        return i + 1;
    }

    void QuickSort_(SyncVector &numbers, int low, int high)
    {
        if (low < high)
        {
            int pi = Partition(numbers, low, high);
            QuickSort_(numbers, low, pi - 1);
            QuickSort_(numbers, pi + 1, high);
        }
    }
};

} // namespace tlr