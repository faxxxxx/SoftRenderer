#include "RasterizationStage.h"
#include "Core/Graphic/Renderer/Rasterizer.h"

<<<<<<< HEAD
=======
static void ScreenMapping(Vector3f &p, int w, int h) {
	p.x = int((p.x + 1.0f) * 0.5f * (w - 1));
	p.y = int((p.y + 1.0f) * 0.5f * (h - 1));
}

>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
bool RasterizationStage::Execute(PipelineContex *ctx) {
	ApplyRasterization(ctx);
	return true;
}

void RasterizationStage::ApplyRasterization(PipelineContex *ctx) {
<<<<<<< HEAD
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
=======
	auto &verts = ctx->_vertexes;
	auto &indexes = ctx->_indexes;
	auto vc = verts.size();
	auto ic = indexes.size();
	if (vc == 0 || ic == 0)
		return;

	auto w = ctx->_pDeviceAPI->PixelWidth();
	auto h = ctx->_pDeviceAPI->PixelHeight();
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55

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
