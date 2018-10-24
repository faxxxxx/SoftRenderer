#include "RasterizationStage.h"
#include "Core/Graphic/Renderer/Rasterizer.h"

static void ScreenMapping(Vector3f &p, int w, int h)
{
    p.x = int((p.x + 1.0f) * 0.5f * (w - 1));
    p.y = int((p.y + 1.0f) * 0.5f * (h - 1));
}

bool RasterizationStage::Execute(PipelineContex *ctx) {
    ApplyRasterization(ctx);
	return true;
}

void RasterizationStage::ApplyRasterization(PipelineContex *ctx) {
    auto &verts = ctx->_vertexes;
    auto &indexes = ctx->_indexes;
    auto vc = verts.size();
    auto ic = indexes.size();
    if (vc == 0 || ic == 0)
        return;
    
    auto w = ctx->_pDeviceAPI->PixelWidth();
    auto h = ctx->_pDeviceAPI->PixelHeight();
    
    for(auto &v : verts) {
        ScreenMapping(v.pos, w, h);
    }
    
    for (int i = 0; i < ic - 2; i+=3) {
        if (indexes[i] < vc && indexes[i + 1] < vc && indexes[i + 2] < vc) {
            auto& v1 = verts[indexes[i]];
            auto& v2 = verts[indexes[i + 1]];
            auto& v3 = verts[indexes[i + 2]];
            if (!ctx->IsWireFrameMode()) {
                Rasterizer::Rasterize(v1, v2, v3, ctx->_fragments);
            }
            else {
                Rasterizer::RasterizeLine(v1.pos, v2.pos, Color(0.0f, 1.0f, 0.0f), ctx->_fragments);
                Rasterizer::RasterizeLine(v3.pos, v2.pos, Color(0.0f, 1.0f, 0.0f), ctx->_fragments);
                Rasterizer::RasterizeLine(v1.pos, v3.pos, Color(0.0f, 1.0f, 0.0f), ctx->_fragments);
            }
        }
    }
}



