#pragma once
#include "SDL.h"
#include "Core/Graphic/Renderer/Renderer.h"

class Application
{
public:
	Application();
	bool Init(int screenWidth, int screenHeight);
	void Run();

private:
	void Loop();

private:
	int _screenWidth = 0;
	int _screenHeight = 0;
	SDL_Window *_pWindow = nullptr;
	Renderer *_pRenderer = nullptr;
};