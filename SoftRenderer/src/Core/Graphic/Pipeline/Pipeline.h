#pragma once
#include "PipelineContex.h"
#include "PipelineStage.h"
#include <vector>

class Pipeline {
 public:
	Pipeline() {}

	void SetContex(PipelineContex *ctx) {
		_pCtx = ctx;
	}
	Pipeline &AddStage(PipelineStage *_pStage);

	void Start();

	PipelineContex* GetContext() {
		return _pCtx;
	}

 private:
	PipelineContex * _pCtx = nullptr;
	std::vector<PipelineStage *> _stages;
};