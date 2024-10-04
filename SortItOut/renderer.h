#pragma once

#define SDL_MAIN_HANDLED
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>

namespace tlr
{

class Renderer
{
public:
	Renderer(int windowWidth, int windowHeight);
	~Renderer();

	/*
	// TODO
	void ClearScreen();
	// TODO
	void DrawSquare();
	// TODO
	void DisplayScreen();
	*/

private:
	const int _WINDOW_WIDTH, _WINDOW_HEIGHT;

	SDL_Window *_window;
	SDL_Renderer *_renderer;

	bool InitSDL();
};

} // namespace tlr