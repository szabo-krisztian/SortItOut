#include "input_manager.h"

namespace tlr
{

void InputManager::Update()
{
	glm::ivec2 position;
	SDL_GetMouseState(&position.x, &position.y);

	while (SDL_PollEvent(&_event))
	{
		bool keyboardEvent = _event.type == SDL_KEYDOWN || _event.type == SDL_KEYUP;
		bool mouseEvent = _event.type == SDL_MOUSEMOTION || _event.type == SDL_MOUSEBUTTONDOWN || _event.type == SDL_MOUSEBUTTONUP;
		if (keyboardEvent)
		{
			ProcessKeyboardEvents();
		}
		else if (mouseEvent)
		{
			ProcessMouseEvents(position);
		}
	}

	UpdateKeyboardHoldEvents();
	UpdateMouseHoldEvents(position);
}

void InputManager::AddKeyboardDownCallback(SDL_Keycode keyCode, KeyboardCallback listener)
{
	_keyboard.downEvents[keyCode] += listener;
}

void InputManager::AddKeyboardUpCallback(SDL_Keycode keyCode, KeyboardCallback listener)
{
	_keyboard.upEvents[keyCode] += listener;
}

void InputManager::AddKeyboardHoldCallback(SDL_Keycode keyCode, KeyboardCallback listener)
{
	_keyboard.holdEvents[keyCode] += listener;
}

void InputManager::AddMouseMotionCallback(MouseCallback listener)
{
	_mouse.cursorMoved += listener;
}

void InputManager::AddMouseDownCallback(Uint8 button, MouseCallback listener)
{
	_mouse.downEvents[button] += listener;
}

void InputManager::AddMouseUpCallback(Uint8 button, MouseCallback listener)
{
	_mouse.upEvents[button] += listener;
}

void InputManager::AddMouseHoldCallback(Uint8 button, MouseCallback listener)
{
	_mouse.holdEvents[button] += listener;
}

void InputManager::ProcessKeyboardEvents()
{
	auto keyCode = _event.key.keysym.sym;

	switch (_event.type)
	{
	case SDL_KEYDOWN:
		_keyboard.downEvents[keyCode].Raise();
		_keyboard.isKeyPressed[keyCode] = true;
		break;

	case SDL_KEYUP:
		_keyboard.upEvents[keyCode].Raise();
		_keyboard.isKeyPressed[keyCode] = false;
		break;
	}
}

void InputManager::ProcessMouseEvents(const glm::ivec2& position)
{
	switch (_event.type)
	{
	case SDL_MOUSEMOTION:
		_mouse.cursorMoved.Raise(position);
		break;

	case SDL_MOUSEBUTTONDOWN:
	{
		auto button = _event.button.button;
		_mouse.downEvents[button].Raise(position);
		_mouse.isKeyPressed[button] = true;
		break;
	}

	case SDL_MOUSEBUTTONUP:
	{
		auto button = _event.button.button;
		_mouse.upEvents[button].Raise(position);
		_mouse.isKeyPressed[button] = false;
		break;
	}

	}
}

void InputManager::UpdateKeyboardHoldEvents()
{
	for (const auto& pair : _keyboard.isKeyPressed)
	{
		if (pair.second)
		{
			_keyboard.holdEvents[pair.first].Raise();
		}
	}
}

void InputManager::UpdateMouseHoldEvents(const glm::ivec2& position)
{
	for (const auto& pair : _mouse.isKeyPressed)
	{
		if (pair.second)
		{
			_mouse.holdEvents[pair.first].Raise(position);
		}
	}
}

} // namespace tlr