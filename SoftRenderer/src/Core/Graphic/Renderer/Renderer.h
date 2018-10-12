#pragma once

#include "SDL.h"
#include "Core/Base/BaseType.h"
#include "../Pipeline/Pipeline.h"

class Renderer
{
public:
	Renderer();
	bool Init(SDL_Window *pWindow);
	void Render();

private:
	void SetupPipeline();
	void DoRender();

private:
	Pipeline *_pPipeline = nullptr;
	DeviceAPI *_pDeviceAPI = nullptr;
};