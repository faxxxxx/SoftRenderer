#pragma once
#include "PipelineStage.h"

class FragmentStage : public PipelineStage {
 public:
	virtual bool Execute(PipelineContex *ctx) override;
};