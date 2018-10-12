#pragma once
#include "PipelineStage.h"

class TestStage : public PipelineStage
{

public:
	virtual bool Execute(PipelineContex *ctx) override
	{
		//for (int i = 0; i < 1000; i++)
		//{
		//	int x = rand() % ctx->_pDeviceAPI->PixelWidth();
		//	int y = rand() % ctx->_pDeviceAPI->PixelHeight();
		//	ctx->_pDeviceAPI->DrawPixel(x, y, Color(1.0f, 0, 0, 1));
		//}
		return true;
	}
};