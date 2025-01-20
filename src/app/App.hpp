#pragma once

#include <vector>
#include <thread>
#include <memory>

#include <SDL2/SDL.h>

#include "AppConfig.hpp"
#include "KeyBindings.hpp"
#include "InputManager.hpp"
#include "Sorting.hpp"
#include "SyncVector.hpp"
#include "Algorithm.hpp"

namespace tlr
{

class App
{
public:
    App(const AppConfig &appConfig);
    ~App();

    void Run();

private:
    const int m_WINDOW_WIDTH;
    const int m_WINDOW_HEIGHT;

    SDL_Window *m_window;
    SDL_Renderer *m_renderer;
    SDL_Surface *m_surface;
    KeyBindings m_keyBindings;
    InputManager &m_inputManager;
    volatile bool m_isAppRunning = true;

    
    void Close_Callback();
    
    std::thread t;
    std::unique_ptr<Algorithm> m_algorithm;
    SyncVector m_numbers;
    
    void Render();
};

} // namespace tlr