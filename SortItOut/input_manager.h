#pragma once

#include <SDL2/SDL.h>
#include "keyboard_state.h"
#include "mouse_state.h"

namespace tlr
{

class InputManager
{
public:
	using KeyboardCallback = void(*)();
	using MouseCallback = void(*)(glm::ivec2);

	void Update();
	
	void AddKeyboardDownCallback(SDL_Keycode keyCode, KeyboardCallback listener);
	void RemoveKeyboardDownCallback(SDL_Keycode keyCode, KeyboardCallback listener);

	void AddKeyboardUpCallback(SDL_Keycode keyCode, KeyboardCallback listener);
	void RemoveKeyboardUpCallback(SDL_Keycode keyCode, KeyboardCallback listener);

	void AddKeyboardHoldCallback(SDL_Keycode keyCode, KeyboardCallback listener);
	void RemoveKeyboardHoldCallback(SDL_Keycode keyCode, KeyboardCallback listener);

	void AddMouseMotionCallback(MouseCallback listener);
	void RemoveMouseMotionCallback(MouseCallback listener);

	void AddMouseDownCallback(Uint8 button, MouseCallback listener);
	void RemoveKeyboardDownCallback(Uint8 button, MouseCallback listener);

	void AddKeyboardUpCallback(Uint8 button, MouseCallback listener);
	void RemoveKeyboardUpCallback(Uint8 button, MouseCallback listener);

	void AddKeyboardHoldCallback(Uint8 button, MouseCallback listener);
	void RemoveKeyboardHoldCallback(Uint8 button, MouseCallback listener);

private:
	SDL_Event     _event;
	KeyboardState _keyboard;
	MouseState    _mouse;

	void ProcessKeyboardEvents();
	void ProcessMouseEvents();
};

} // namespace tlr