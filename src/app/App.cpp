#include "App.hpp"

#include <cassert>

namespace tlr
{

App::App(const AppConfig &appConfig) :
    m_WINDOW_WIDTH(appConfig.windowWidth),
    m_WINDOW_HEIGHT(appConfig.windowHeight),
    m_inputManager(InputManager::GetInstance())
{
    assert(SDL_Init(SDL_INIT_VIDEO) == 0 && "SDL init error");
    m_window = SDL_CreateWindow("Sort it out", appConfig.windowPosX, appConfig.windowPosY, m_WINDOW_WIDTH, m_WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
    assert(m_window != nullptr && "SDL window creation error");
    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
    assert(m_renderer != nullptr && "SDL renderer creation error");
    m_surface = SDL_GetWindowSurface(m_window);
    assert(m_surface != nullptr && "SDL surface creation error");

    m_inputManager.KeyPressed[m_keyBindings.CloseButton][KMOD_NONE].RegisterCallback(this, &App::Close_Callback);
}

App::~App()
{
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

void App::Run()
{
    SDL_Rect rect{0, 0, 100, 100};
    SDL_Color color{255, 255, 255, 255};

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
    
}

} // namespace tlr