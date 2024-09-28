#pragma once

#include "renderer.h"

namespace tlr
{

class App
{
public:
	App(int windowWidth, int windowHeight);

	void Run();

private:
	Renderer _renderer;

};

} // namespace tlr