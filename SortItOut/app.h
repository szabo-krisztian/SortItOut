#pragma once

#include "renderer.h"
#include "input_manager.h"

namespace tlr
{

class App
{
public:
	App(int windowWidth, int windowHeight);

	void Run();
	
private:
	bool		 _userWantsToQuit = false;
	Renderer	 _renderer;
	InputManager _inputManager;

	void Quit();
};

} // namespace tlr