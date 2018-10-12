#include "Application.h"
#include "SDL.h"
#include <iostream>

Application::Application()
{
}

bool Application::Init(int screenWidth, int screenHeight)
{
	_screenWidth = screenWidth;
	_screenHeight = screenHeight;

	bool ret = false;
	do 
	{
		if (_screenWidth <= 0 || _screenHeight <= 0)
		{
			break;
		}

		if (SDL_Init(SDL_INIT_EVERYTHING) < 0)
		{
			std::cout << "SDL initialize fail: " << SDL_GetError() << std::endl;
			break;
		}

		_pWindow = SDL_CreateWindow("SDL", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, _screenWidth, _screenHeight, SDL_WINDOW_SHOWN);
		if (!_pWindow)
		{
			std::cout << "Create window fail : " << SDL_GetError() << std::endl;
			break;
		}

		_pRenderer = new Renderer();
		if (!_pRenderer || !_pRenderer->Init(_pWindow))
		{
			std::cout << "Create _pRenderer fail" << std::endl;
			break;
		}

		ret = true;
	} while (0);
	return ret;
}

void Application::Run()
{
	Loop();
}

void Application::Loop()
{
	SDL_Event sldEvent;
	bool bQuit = false;
	while (!bQuit)
	{
		while (SDL_PollEvent(&sldEvent))
		{
			switch (sldEvent.type)
			{
			case SDL_QUIT:
				bQuit = true;
				break;
			}
		}

		_pRenderer->Render();
	}
}