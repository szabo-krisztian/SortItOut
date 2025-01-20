#include "App.hpp"

#include <cassert>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

#include "MergeSort.hpp"

namespace tlr
{

App::App(const AppConfig &appConfig) :
    m_WINDOW_WIDTH(appConfig.windowWidth),
    m_WINDOW_HEIGHT(appConfig.windowHeight),
    m_inputManager(InputManager::GetInstance()),
    m_numbers(appConfig.numberCount, appConfig.swapTimeInMillis),
    m_algorithm(std::make_unique<MergeSort>(m_isAppRunning))
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0 && "SDL init error");
    m_window = SDL_CreateWindow("Sort it out", appConfig.windowPosX, appConfig.windowPosY, m_WINDOW_WIDTH, m_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    assert(m_window != nullptr && "SDL window creation error");
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert(m_renderer != nullptr && "SDL renderer creation error");
    m_surface = SDL_GetWindowSurface(m_window);
    assert(m_surface != nullptr && "SDL surface creation error");

    m_inputManager.KeyPressed[m_keyBindings.close][KMOD_NONE].RegisterCallback(this, &App::Close_Callback);

    t = std::thread(&Algorithm::Sort, m_algorithm.get(), std::ref(m_numbers));
}

App::~App()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void App::Run()
{
    while (m_isAppRunning)
    {
        m_inputManager.Update();

        SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
        SDL_RenderClear(m_renderer);

        Render();

        SDL_RenderPresent(m_renderer);
    }
}

void App::Close_Callback()
{
    m_isAppRunning = false;
    t.join();
}

void App::Render()
{
    static const float RECT_SIZE = m_WINDOW_HEIGHT / static_cast<float>(m_numbers.size() + 1);
    static const float LEFTOVER = (m_WINDOW_WIDTH - m_numbers.size() * RECT_SIZE) / static_cast<float>(m_numbers.size() - 1);

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    m_numbers.Lock();
    for (std::size_t i = 0; i < m_numbers.size(); ++i)
    {
        SDL_Rect rect;
        rect.h = RECT_SIZE * m_numbers[i];
        rect.w = RECT_SIZE;
        rect.x = static_cast<int>(i) * (RECT_SIZE + LEFTOVER);
        rect.y = m_WINDOW_HEIGHT - rect.h;

        SDL_RenderFillRect(m_renderer, &rect);
    }
    m_numbers.Unlock();
}

} // namespace tlr