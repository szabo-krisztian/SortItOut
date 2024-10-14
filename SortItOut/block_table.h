#pragma once

#include <vector>

namespace tlr
{

class BlockTable
{
public:
	BlockTable(std::size_t width, std::size_t height);

private:
	const std::size_t _WIDTH;
	const std::size_t _HEIGHT;
};

} // namespace tlr