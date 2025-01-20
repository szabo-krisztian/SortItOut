#include "App.hpp"

#include <cassert>
#include <numeric>
#include <algorithm>
#include <random>
#include <chrono>
#include <thread>

#include "Algorithms.hpp"

namespace tlr
{

App::App(const AppConfig &appConfig) :
    m_WINDOW_WIDTH(appConfig.windowWidth),
    m_WINDOW_HEIGHT(appConfig.windowHeight),
    m_inputManager(InputManager::GetInstance()),
    m_numbers(appConfig.numberCount, appConfig.swapTimeInMillis),
    m_algorithm(std::make_unique<QuickSort>(m_isAppRunning))
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0 && "SDL init error");
    m_window = SDL_CreateWindow("Sort it out", appConfig.windowPosX, appConfig.windowPosY, m_WINDOW_WIDTH, m_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    assert(m_window != nullptr && "SDL window creation error");
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert(m_renderer != nullptr && "SDL renderer creation error");
    m_surface = SDL_GetWindowSurface(m_window);
    assert(m_surface != nullptr && "SDL surface creation error");

    m_inputManager.KeyPressed[m_keyBindings.close][KMOD_NONE].RegisterCallback(this, &App::Close_Callback);
    m_inputManager.AllEvent.RegisterCallback(this, &App::ReadAlgorithmFromUser_Callback);
}

App::~App()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void App::Run()
{
    AlgorithmFactory::PrintAlgorithms();

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
}

void App::Render()
{
    // TODO: clean this
    static const float RECT_SIZE = m_WINDOW_HEIGHT / static_cast<float>(m_numbers.size() + 1);
    static const int ROUNDED_RECT_SIZE = static_cast<int>(std::round(RECT_SIZE));
    static const int BETWEEN_GAP_SIZE = static_cast<int>((m_WINDOW_WIDTH - m_numbers.size() * ROUNDED_RECT_SIZE) / static_cast<float>(m_numbers.size() - 1));
    static const int SIDES_GAP_SIZE = static_cast<int>((m_WINDOW_WIDTH - (m_numbers.size() * (ROUNDED_RECT_SIZE + BETWEEN_GAP_SIZE) - BETWEEN_GAP_SIZE)) / 2);

    SDL_SetRenderDrawColor(m_renderer, 255, 255, 255, 255);
    m_numbers.Lock();
    for (std::size_t i = 0; i < m_numbers.size(); ++i)
    {
        SDL_Rect rect;
        rect.h = static_cast<int>(RECT_SIZE * m_numbers[i]);
        rect.w = ROUNDED_RECT_SIZE;
        rect.x = SIDES_GAP_SIZE + (static_cast<int>(i) * (ROUNDED_RECT_SIZE + BETWEEN_GAP_SIZE));
        rect.y = m_WINDOW_HEIGHT - rect.h;

        SDL_RenderFillRect(m_renderer, &rect);
    }
    m_numbers.Unlock();
}

void App::ReadAlgorithmFromUser_Callback(const SDL_Event &event)
{
    if (event.type != SDL_KEYDOWN) { return; }

    bool isTaskStillRunning = m_sortingTask.valid() && m_sortingTask.wait_for(std::chrono::milliseconds(0)) != std::future_status::ready;
    if (isTaskStillRunning) { return; }

    m_algorithm = AlgorithmFactory::MakeAlgorithm(event.key.keysym.sym, m_isAppRunning);
    if (m_algorithm != nullptr)
    {
        m_numbers.Shuffle();
        m_sortingTask = std::async(std::launch::async, &Algorithm::Sort, m_algorithm.get(), std::ref(m_numbers));
    }
}

} // namespace tlr