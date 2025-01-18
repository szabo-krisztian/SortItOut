#include <SDL2/SDL.h>

#include "AppConfig.hpp"
#include "KeyBindings.hpp"
#include "InputManager.hpp"

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
    bool m_isAppRunning = true;
    
    
    void Close_Callback();

    void Render();
};

} // namespace tlr