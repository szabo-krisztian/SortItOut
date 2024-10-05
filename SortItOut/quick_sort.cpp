#include "quick_sort.h"
#include <utility>

namespace tlr
{

void QuickSort::Sort(std::vector<int>& numbers)
{
    QuickSort_(numbers, 0, numbers.size() - 1);
}

void QuickSort::QuickSort_(std::vector<int>& numbers, std::size_t low, std::size_t high)
{
    while (low < high)
    {
        std::size_t i = low;
        std::size_t j = high;
        int pivot = numbers[(i + j) / 2];

        while (i <= j)
        {
            while (numbers[i] < pivot)
            {
                i++;
            }
            while (numbers[j] > pivot)
            {
                j--;
            }
            if (i <= j)
            {
                std::swap(numbers[i], numbers[j]);
                i++;
                j--;
            }
        }

        if (low < j)
        {
            QuickSort_(numbers, low, j);
        }

        low = i;
    }
}

} // namespace tlr