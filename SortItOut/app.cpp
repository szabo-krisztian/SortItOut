#include "app.h"
#include <iostream>
#include "quick_sort.h"


namespace tlr
{

App::App(int windowWidth, int windowHeight) : _renderer(windowWidth, windowHeight)
{
	_inputManager.AddKeyboardDownCallback(SDLK_ESCAPE, [this]() { Quit(); });
}

void print(std::vector<int>& k)
{
	for (auto& i : k)
	{
		std::cout << i << " ";
	}
	std::cout << std::endl;
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