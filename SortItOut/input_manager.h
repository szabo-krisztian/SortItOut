#pragma once

#include <SDL2/SDL.h>
#include "keyboard_state.h"
#include "mouse_state.h"

namespace tlr
{

class InputManager
{
public:
	void Update();
	
	void AddKeyDownCallback(SDL_Keycode code, void(*listener)())
	{
		_keyDownListeners[code] += listener;
	}
	void RemoveKeyDownCallback(SDL_Keycode code, void(*listener)())
	{
		_keyDownListeners[code] -= listener;
	}

	void AddKeyUpCallback(SDL_Keycode code, void(*listener)())
	{
		_keyUpListeners[code] += listener;
	}
	void RemoveKeyUpCallback(SDL_Keycode code, void(*listener)())
	{
		_keyUpListeners[code] -= listener;
	}

	void AddKeyHoldCallback(SDL_Keycode code, void(*listener)())
	{
		_keyHoldListeners[code] += listener;
	}
	void RemoveKeyHoldCallback(SDL_Keycode code, void(*listener)())
	{
		_keyHoldListeners[code] -= listener;
	}



private:
	SDL_Event     _event;
	KeyboardState _keyboard;
	MouseState    _mouse;

	void ProcessKeyboardEvents();
	void ProcessMouseEvents();
};

} // namespace tlr