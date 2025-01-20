#pragma once

#include <memory>
#include <iostream>

#include <SDL2/SDL.h>

#include "Algorithm.hpp"
#include "QuickSort.hpp"
#include "MergeSort.hpp"
#include "SelectionSort.hpp"

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
            return std::make_unique<QuickSort>(isAppRunning);
            
        case SDLK_2:
            return std::make_unique<MergeSort>(isAppRunning);

        case SDLK_3:
            return std::make_unique<SelectionSort>(isAppRunning);
        }

        return nullptr;
    }

    static void PrintAlgorithms()
    {
        std::cout << "Press a key to choose an algorithm:" << std::endl <<
            "\t[1] - Quick sort" << std::endl <<
            "\t[2] - Merge sort" << std::endl <<
            "\t[3] - Selection sort" << std::endl;
    }
};

} // namespace tlr