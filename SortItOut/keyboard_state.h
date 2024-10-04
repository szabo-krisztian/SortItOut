#pragma once

#include <unordered_map>

#include <SDL2/SDL.h>
#include "event.hpp"

namespace tlr
{

struct KeyboardState
{
	using ButtonEventMap = std::unordered_map<SDL_Keycode, Event<void>>;	
	using ButtonStateMap = std::unordered_map<SDL_Keycode, bool>;

	ButtonStateMap isKeyPressed;
	ButtonEventMap downEvents;
	ButtonEventMap upEvents;
	ButtonEventMap holdEvents;
};

} // namespace tlr