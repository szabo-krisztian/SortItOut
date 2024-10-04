#pragma once

#include <SDL2/SDL.h>
#include "keyboard_state.h"
#include "mouse_state.h"

namespace tlr
{

class InputManager
{
public:
	using KeyboardCallback = std::function<void()>;
	using MouseCallback = std::function<void(const glm::ivec2&)>;

	void Update();
	
	void AddKeyboardDownCallback(SDL_Keycode keyCode, KeyboardCallback listener);
	void AddKeyboardUpCallback(SDL_Keycode keyCode, KeyboardCallback listener);
	void AddKeyboardHoldCallback(SDL_Keycode keyCode, KeyboardCallback listener);

	void AddMouseMotionCallback(MouseCallback listener);
	void AddMouseDownCallback(Uint8 button, MouseCallback listener);
	void AddKeyboardUpCallback(Uint8 button, MouseCallback listener);
	void AddKeyboardHoldCallback(Uint8 button, MouseCallback listener);
	
private:
	SDL_Event     _event;
	KeyboardState _keyboard;
	MouseState    _mouse;

	void ProcessKeyboardEvents();
	void ProcessMouseEvents(const glm::ivec2& position);
	void UpdateKeyboardHoldEvents();
	void UpdateMouseHoldEvents(const glm::ivec2& position);
};

} // namespace tlr