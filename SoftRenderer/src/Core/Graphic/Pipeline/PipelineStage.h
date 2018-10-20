#pragma once
#include "PipelineContex.h"

class PipelineStage {
 public:
	PipelineStage() {}
	virtual ~PipelineStage() {}
	virtual void Init(PipelineContex *ctx) {}
	virtual bool Execute(PipelineContex *ctx) = 0;
};
