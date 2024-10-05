#pragma once

#include "isorter.h"

namespace tlr
{

class QuickSort : public ISorter
{
public:
	void Sort(std::vector<int>& numbers) override;

private:
	void QuickSort_(std::vector<int>& numbers, std::size_t low, std::size_t high);
};

} // namespace tlr