#include "RasterizationStage.h"
#include "Core/Graphic/Renderer/Rasterizer.h"

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
    
    for (int i = 0; i < ic - 2; i+=3) {
        if (indexes[i] < vc && indexes[i + 1] < vc && indexes[i + 2] < vc) {
            auto& v1 = verts[indexes[i]];
            auto& v2 = verts[indexes[i + 1]];
            auto& v3 = verts[indexes[i + 2]];
            if (!ctx->IsWireFrameMode()) {
                Rasterizer::Rasterize(v1, v2, v3, ctx->_fragments);
            }
            else {
                Color c(0.0f, 1.0f, 0.0f);
                Rasterizer::RasterizeLine(v1.pos, v2.pos, c, ctx->_fragments);
                Rasterizer::RasterizeLine(v3.pos, v2.pos, c, ctx->_fragments);
                Rasterizer::RasterizeLine(v1.pos, v3.pos, c, ctx->_fragments);
            }
        }
    }
}



