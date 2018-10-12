#pragma once
#include "PipelineContex.h"

class PipelineStage
{
public:
	PipelineStage() {}
	virtual ~PipelineStage() {}
	virtual bool Execute(PipelineContex *ctx) = 0;
};
