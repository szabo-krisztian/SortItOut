#pragma once

#include <unordered_map>

#include <SDL2/SDL.h>
#include "event.hpp"

namespace tlr
{

class InputManager
{
public:
	void Update()
	{
		while (SDL_PollEvent(&_event))
		{
			switch (_event.type)
			{
			case SDL_KEYDOWN:
				_keyDownListeners[_event.key.keysym.sym].Raise();
				_isKeyPressed[_event.key.keysym.sym] = true;
				break;

			case SDL_KEYUP:
				_keyUpListeners[_event.key.keysym.sym].Raise();
				_isKeyPressed[_event.key.keysym.sym] = false;
				break;
			}
		}

		for (const auto& pair : _isKeyPressed)
		{
			if (pair.second)
			{
				_keyHoldListeners[pair.first].Raise();
			}
		}
	}
	
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
	using KeyStateMap = std::unordered_map<SDL_Keycode, bool>;
	using KeyEventMap = std::unordered_map<SDL_Keycode, Event<void>>;
	using CursorEvent = Event<void, float, float>;
	
	SDL_Event	_event;
	KeyStateMap _isKeyPressed;

	CursorEvent _cursorMovedListeners;
	KeyEventMap	_keyHoldListeners;
	KeyEventMap	_keyDownListeners;
	KeyEventMap	_keyUpListeners;
};

} // namespace tlr