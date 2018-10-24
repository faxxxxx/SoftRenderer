#include "FragmentStage.h"
#include "Core/Graphic/Texture/Texture.h"

Texture *pTex = nullptr;

void FragmentStage::Init(PipelineContex *ctx) {
    pTex = new Texture();
    pTex->Load("box.png");
}

bool FragmentStage::Execute(PipelineContex * ctx) {
    auto w = ctx->_pDeviceAPI->PixelWidth();
    auto h = ctx->_pDeviceAPI->PixelHeight();
    auto maxIdx = w * h;
    Color c;
	for (auto& frag : ctx->_fragments) {
		int idx = ToBufferIndex(frag.pos, ctx);
        
        if (idx < 0 || idx >= maxIdx)
            continue;
        
		if (ZTestPass(idx, frag.pos.z, ctx)) {
            c = ctx->IsWireFrameMode() ? frag.color : pTex->GetColor(frag.uv);
            ColorBlend(idx, c, ctx);
		}
	}
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            auto &c = ctx->_colorBuffer[i * w + j];
            ctx->_pDeviceAPI->DrawPixel(j, (h-i-1), c);
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
	return pos.y * w + pos.x;
}
