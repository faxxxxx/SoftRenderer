#include "FragmentStage.h"

bool FragmentStage::Execute(PipelineContex * ctx) {
	for (auto& frag : ctx->_fragments) {
		int idx = ToBufferIndex(frag.pos, ctx);
		if (ZTestPass(idx, frag.pos.z, ctx)) {
			ColorBlend(idx, frag.color, ctx);
		}
	}
	return false;
}

bool FragmentStage::ZTestPass(int idx, float newz, PipelineContex *ctx) {
	float oldz = ctx->_depthBuffer[idx];
	if (newz <= oldz) {
		ctx->_depthBuffer[idx] = newz;
		return true;
	}
	return false;
}

void FragmentStage::ColorBlend(int idx, const Color &c, PipelineContex *ctx) {
	ctx->_colorBuffer[idx] = c;
}

int FragmentStage::ToBufferIndex(const Vector3f &pos, PipelineContex *ctx) {
	auto w = ctx->_pDeviceAPI->PixelWidth();
	auto h = ctx->_pDeviceAPI->PixelHeight();
	int x = (int)((pos.x + 2) * 0.5f * w);
	int y = (int)((pos.y + 2) * 0.5f * h);
	return y * w + x;
}
