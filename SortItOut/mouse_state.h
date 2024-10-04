#pragma once

#include <unordered_map>

#include <SDL2/SDL.h>
#include <glm/glm.hpp>
#include "event.hpp"

namespace tlr
{

struct MouseState
{
	using ButtonEventMap = std::unordered_map<Uint8, Event<void, glm::ivec2>>;
	using ButtonStateMap = std::unordered_map<Uint8, bool>;

	ButtonStateMap isKeyPressed;
	ButtonEventMap downEvents;
	ButtonEventMap upEvents;
	ButtonEventMap holdEvents;
	Event<void, glm::ivec2> cursorMoved;
};

} // namespace tlr
