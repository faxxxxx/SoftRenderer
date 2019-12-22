#include "Renderer.h"
#include <iostream>
#include "Core/Graphic/Pipeline/TestStage.h"
#include "Core/Graphic/Pipeline/TestStage2.h"
#include "Core/Graphic/Pipeline/FragmentStage.h"
#include "Core/Graphic/Pipeline/ScreenMappingStage.h"
#include "Core/Graphic/Pipeline/RasterizationStage.h"
#include "DeviceAPI.h"

Renderer::Renderer() {
}

bool Renderer::Init(SDL_Window * pWindow) {
	bool ret = false;
	do {
		BREAK_IF(!pWindow);
		_pDeviceAPI = DeviceAPI::Create(pWindow);
		BREAK_IF(!_pDeviceAPI);

		SetupPipeline();

		ret = true;
	} while (0);
	return ret;
}

void Renderer::Render() {
	if (!_pDeviceAPI) {
		return;
	}

	_pDeviceAPI->BeginRender();
	DoRender();
	_pDeviceAPI->EndRender();
}

void Renderer::SetupPipeline() {
	_pPipeline = new Pipeline();
	auto *pCtx = new PipelineContex();
	pCtx->Init(_pDeviceAPI);
	_pPipeline->SetContex(pCtx);
	_pPipeline->AddStage(new TestStage())
	.AddStage(new TestStage2())
    .AddStage(new ScreenMappingStage())
	.AddStage(new RasterizationStage())
	.AddStage(new FragmentStage());
}

void Renderer::DoRender() {
	auto ctx = _pPipeline->GetContext();
	ctx->Clear();

	_pPipeline->Start();
}
