#pragma once
#include "PipelineStage.h"

class RasterizationStage : public PipelineStage {
 public:
	virtual bool Execute(PipelineContex *ctx) override;
    
private:
    void ApplyRasterization(PipelineContex *ctx);
};
