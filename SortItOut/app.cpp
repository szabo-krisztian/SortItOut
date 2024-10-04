#include "app.h"
#include <iostream>

namespace tlr
{

App::App(int windowWidth, int windowHeight) : _renderer(windowWidth, windowHeight)
{
	_inputManager.AddKeyboardDownCallback(SDLK_ESCAPE, [this]() { Quit(); });


}

void App::Run()
{
	while (!_userWantsToQuit)
	{
		_inputManager.Update();
	}
}

void App::Quit()
{
	_userWantsToQuit = true;
}

} // namespace tlr