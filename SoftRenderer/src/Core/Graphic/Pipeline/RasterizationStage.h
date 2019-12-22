#pragma once
#include "PipelineStage.h"

class RasterizationStage : public PipelineStage {
 public:
	virtual bool Execute(PipelineContex *ctx) override;

 private:
	void ApplyRasterization(PipelineContex *ctx);
	bool TriangleCW(const Vector3f &v1, const Vector3f &v2, const Vector3f &v3);
};
