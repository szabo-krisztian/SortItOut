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

			case SDL_MOUSEMOTION:
				break;

			case SDL_MOUSEBUTTONDOWN:
				break;

			case SDL_MOUSEBUTTONUP:
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
	template<typename T>
	using ButtonEventMap = std::unordered_map<T, Event<void>>;

	struct
	{
		ButtonEventMap<SDL_Keycode> downListeners;
		ButtonEventMap<SDL_Keycode> upListeners;
		ButtonEventMap<SDL_Keycode> holdListeners;
	} _keyboard;

	struct
	{
		ButtonEventMap<Uint8> downListeners;
		ButtonEventMap<Uint8> upListeners;
		ButtonEventMap<Uint8> holdListeners;
	} _cursor;

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