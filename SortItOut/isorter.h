#pragma once

#include <vector>

namespace tlr
{

class ISorter
{
public:
	virtual ~ISorter() = default;
	virtual void Sort(std::vector<int>& numbers) = 0;
};

} // namespace tlr