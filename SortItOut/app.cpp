#include "app.h"
#include <iostream>

namespace tlr
{

void printsm(const glm::ivec2& position)
{
	std::cout << position.x << ", " << position.y << std::endl;
}

App::App(int windowWidth, int windowHeight) : _renderer(windowWidth, windowHeight)
{
	
	_inputManager.AddMouseMotionCallback(printsm);
}

void App::Run()
{
	while (true)
	{
		_inputManager.Update();
	}
}

} // namespace tlr