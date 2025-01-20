#pragma once

#include "Algorithm.hpp"

namespace tlr
{
    
class MergeSort final : public Algorithm
{
public:
    MergeSort(volatile bool &isAppRunning) : Algorithm(isAppRunning) {}

    void Sort(SyncVector &numbers) override
    {
        MergeSort_(numbers, 0, static_cast<int>(numbers.size() - 1));
    }

private:
    void Merge(SyncVector &arr, int left, int mid, int right)
    {
        int n1 = mid - left + 1;
        int n2 = right - mid;

        std::vector<int> L(n1), R(n2);

        for (int i = 0; i < n1; ++i)
        {
            L[i] = arr[left + i];
        }
        for (int j = 0; j < n2; ++j)
        {
            R[j] = arr[mid + 1 + j];
        }
            
        int i = 0, j = 0;
        int k = left;
        
        while (i < n1 && j < n2)
        {
            if (L[i] <= R[j])
            {
                arr.Assign(k, L[i]);
                ++i;
            }
            else
            {
                arr.Assign(k, R[j]);
                ++j;
            }
            ++k;
        }

        
        while (i < n1)
        {
            arr.Assign(k, L[i]);
            i++;
            k++;
        }

        while (j < n2)
        {
            arr.Assign(k, R[j]);
            j++;
            k++;
        }
    }

    void MergeSort_(SyncVector &numbers, int left, int right)
    {
        if (left >= right)
        return;

        int mid = left + (right - left) / 2;

        if (!m_isAppRunning) { return; }
        MergeSort_(numbers, left, mid);
        
        if (!m_isAppRunning) { return; }
        MergeSort_(numbers, mid + 1, right);

        if (!m_isAppRunning) { return; }
        Merge(numbers, left, mid, right);
    }
};

} // namespace tlr