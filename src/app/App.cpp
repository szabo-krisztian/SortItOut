#include "App.hpp"

#include <cassert>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

namespace tlr
{

App::App(const AppConfig &appConfig) :
    m_WINDOW_WIDTH(appConfig.windowWidth),
    m_WINDOW_HEIGHT(appConfig.windowHeight),
    m_inputManager(InputManager::GetInstance()),
    m_numbers(appConfig.numberCount)
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0 && "SDL init error");
    m_window = SDL_CreateWindow("Sort it out", appConfig.windowPosX, appConfig.windowPosY, m_WINDOW_WIDTH, m_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    assert(m_window != nullptr && "SDL window creation error");
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert(m_renderer != nullptr && "SDL renderer creation error");
    m_surface = SDL_GetWindowSurface(m_window);
    assert(m_surface != nullptr && "SDL surface creation error");

    m_inputManager.KeyPressed[m_keyBindings.close][KMOD_NONE].RegisterCallback(this, &App::Close_Callback);

    t = std::thread(&App::StartSorting, this);
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

void App::StartSorting()
{
    
    
    while (true)
    {
        m_numbers.Lock();
        m_numbers.Shuffle();
        m_numbers.Unlock();

        std::this_thread::sleep_for(std::chrono::milliseconds(50));

        
        bool isSorted = true;
        for (std::size_t i = 1; i < m_numbers.size(); ++i)
        {
            if (m_numbers[i] - m_numbers[i - 1] < 0) { isSorted = false; break; }
        }
        if (isSorted) {break;}
    }
    

    
    /*
    for (std::size_t i = 0; i < m_numbers.size() - 1; ++i)
    {
        for (std::size_t j = i + 1; j < m_numbers.size(); ++j)
        {
            if (m_numbers[i] < m_numbers[j])
            {
                m_numbers.Swap(i, j);
            }
        }
    }
    */
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