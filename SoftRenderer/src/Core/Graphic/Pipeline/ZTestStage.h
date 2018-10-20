#pragma once
#include "PipelineStage.h"

class ZTestStage : public PipelineStage {
 public:
	virtual void Init(PipelineContex *ctx) override {
		int size = ctx->_pDeviceAPI->PixelWidth() * ctx->_pDeviceAPI->PixelHeight();
		_depthBuffer = new char[size];
		memset(_depthBuffer, 0, size);
	}

	virtual bool Execute(PipelineContex *ctx) override {
		return true;
	}



 private:
	char *_depthBuffer;
};