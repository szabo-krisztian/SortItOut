#include "app.h"
#include <iostream>
#include "quick_sort.h"


namespace tlr
{

App::App(int windowWidth, int windowHeight) : _renderer(windowWidth, windowHeight)
{	
	InitCallbacks();
}

void App::Run()
{
	while (!_userWantsToQuit)
	{
		_inputManager.Update();
	}
}

void App::InitCallbacks()
{
	_inputManager.AddMouseDownCallback(SDL_BUTTON_LEFT, [this] (const glm::ivec2& position) {
		PlaceSquareCallback(position);
	});
}

void App::QuitCallback()
{
	_userWantsToQuit = true;
}

void App::PlaceSquareCallback(const glm::ivec2& posistion)
{
	std::cout << "place" << std::endl;
}

} // namespace tlr