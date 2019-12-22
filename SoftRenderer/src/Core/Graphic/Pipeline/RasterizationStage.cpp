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
            } else {
                Rasterizer::RasterizeLine(v1.pos, v2.pos, Color(0.0f, 1.0f, 0.0f), ctx->_fragments);
                Rasterizer::RasterizeLine(v3.pos, v2.pos, Color(0.0f, 1.0f, 0.0f), ctx->_fragments);
                Rasterizer::RasterizeLine(v1.pos, v3.pos, Color(0.0f, 1.0f, 0.0f), ctx->_fragments);
            }
        }
    }
}


bool RasterizationStage::TriangleCW(const Vector3f & v1, const Vector3f & v2, const Vector3f & v3) {
	//Vector3f v1v2(v2.x - v1.x, v2.y - v1.y, v2.z - v1.z);
	//Vector3f v2v3(v3.x - v2.x, v3.y - v2.y, v3.z - v2.z);
	//return v1v2.Dot(v2v3) <= 0;
	return true;
}
