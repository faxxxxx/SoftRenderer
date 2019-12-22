#include "FragmentStage.h"
#include "Core/Graphic/Texture/Texture.h"

Texture *pTex = nullptr;



void FragmentStage::Init(PipelineContex *ctx) {
<<<<<<< HEAD
    pTex = new Texture();
    pTex->Load("icon.png");
}

bool FragmentStage::Execute(PipelineContex * ctx) {
    auto w = ctx->_pDeviceAPI->PixelWidth();
    auto h = ctx->_pDeviceAPI->PixelHeight();
    auto maxIdx = (w - 1) * (h - 1);
    Color c;
=======
	pTex = new Texture();
	pTex->Load("box.png");
}

bool FragmentStage::Execute(PipelineContex * ctx) {
	auto w = ctx->_pDeviceAPI->PixelWidth();
	auto h = ctx->_pDeviceAPI->PixelHeight();
	auto maxIdx = w * h;
	Color c;
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
	for (auto& frag : ctx->_fragments) {
		int idx = ToBufferIndex(frag.pos, ctx);

		if (idx < 0 || idx >= maxIdx)
			continue;

		if (ZTestPass(idx, frag.pos.z, ctx)) {
			c = ctx->IsWireFrameMode() ? frag.color : pTex->GetColor(frag.uv);
			ColorBlend(idx, c, ctx);
		}
	}
<<<<<<< HEAD
    
    ctx->CheckColorBuffer(Color(0, 1.0f, 0, 1.0f));
    
    for(int i = 0; i < h; i++)
    {
        for(int j = 0; j < w; j++)
        {
            auto &c = ctx->_colorBuffer[i * w + j];
            ctx->_pDeviceAPI->DrawPixel(j, (h-i-1), c);
        }
    }
    
=======

	for(int i = 0; i < h; i++) {
		for(int j = 0; j < w; j++) {
			auto &c = ctx->_colorBuffer[i * w + j];
			ctx->_pDeviceAPI->DrawPixel(j, (h-i-1), c);
		}
	}

>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
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

int FragmentStage::ToBufferIndex(const Vector4f &pos, PipelineContex *ctx) {
	auto w = ctx->_pDeviceAPI->PixelWidth();
    auto h = ctx->_pDeviceAPI->PixelHeight();
    if (pos.x > w - 1 || pos.x < 0)
        return -1;
    if (pos.y > h - 1 || pos.y < 0)
        return -1;
    
	return pos.y * w + pos.x;
}
