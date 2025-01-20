#pragma once

#include <memory>

#include "Algorithm.hpp"
#include "QuickSort.hpp"
#include "MergeSort.hpp"
#include <iostream>
namespace tlr
{

class AlgorithmFactory
{
public:
    static std::unique_ptr<Algorithm> MakeAlgorithm(SDL_Keycode order, volatile bool &isAppRunning)
    {
        switch (order)
        {
        case SDLK_1:
        {
            std::cout << "QUICK" << std::endl;
            return std::make_unique<QuickSort>(isAppRunning);
        }
            
        case SDLK_2:
        {
            std::cout << "MERGE" << std::endl;
            return std::make_unique<MergeSort>(isAppRunning);
        }
            
        }
        return nullptr;
    }
};

} // namespace tlr