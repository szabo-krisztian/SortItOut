#pragma once

#include <vector>
#include <future>
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
    void ReadAlgorithmFromUser_Callback(const SDL_Event &event);

    SyncVector m_numbers;
    std::unique_ptr<Algorithm> m_algorithm;
    std::future<void> m_sortingTask;
    
    void Render();
};

} // namespace tlr