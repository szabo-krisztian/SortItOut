#pragma once

#include <SDL2/SDL.h>

namespace tlr
{

struct KeyBindings
{
    SDL_Keycode close = SDLK_ESCAPE;
    SDL_Keycode startSorting = SDLK_SPACE;
};

} // namespace tlr