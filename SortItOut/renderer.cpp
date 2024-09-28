#include <iostream>
#include <cassert>

#include "renderer.h"

namespace tlr
{

Renderer::Renderer(int windowWidth, int windowHeight) : _WINDOW_WIDTH(windowWidth), _WINDOW_HEIGHT(windowHeight)
{
	assert(InitSDL() && "failed to initialize renderer");
}

Renderer::~Renderer()
{
	SDL_DestroyRenderer(_renderer);
	SDL_DestroyWindow(_window);
}

bool Renderer::InitSDL()
{
	SDL_LogSetPriority(SDL_LOG_CATEGORY_ERROR, SDL_LOG_PRIORITY_ERROR);
	if (SDL_Init(SDL_INIT_VIDEO) == -1)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "error during the SDL initialization : %s", SDL_GetError());
		return false;
	}
	std::atexit(SDL_Quit);

	_window = SDL_CreateWindow("SortItOut", 100, 100, _WINDOW_WIDTH, _WINDOW_HEIGHT, SDL_WINDOW_SHOWN);
	if (!_window)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "error during the SDL initialization: %s", SDL_GetError());
		return false;
	}

	_renderer = SDL_CreateRenderer(_window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
	if (!_renderer)
	{
		SDL_LogError(SDL_LOG_CATEGORY_ERROR, "error during the creation of an SDL _renderer : %s", SDL_GetError());
		SDL_DestroyWindow(_window);
		return false;
	}
}

} // namespace tlr