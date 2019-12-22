#pragma once
#include "PipelineStage.h"

class FragmentStage : public PipelineStage {
 public:
    virtual void Init(PipelineContex *ctx) override;
	virtual bool Execute(PipelineContex *ctx) override;

 private:
	bool ZTestPass(int idx, float newz, PipelineContex *ctx);
	void ColorBlend(int idx, const Color &c, PipelineContex *ctx);
	int ToBufferIndex(const Vector4f &pos, PipelineContex *ctx);
};
