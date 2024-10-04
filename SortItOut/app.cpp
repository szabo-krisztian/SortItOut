#include "app.h"
#include <iostream>

namespace tlr
{

void printsm()
{
	std::cout << "pressed" << std::endl;
}

App::App(int windowWidth, int windowHeight) : _renderer(windowWidth, windowHeight)
{
	_inputManager.AddKeyboardHoldCallback(SDLK_w, printsm);
}

void App::Run()
{
	while (true)
	{
		_inputManager.Update();
	}
}

} // namespace tlr