#include "RasterizationStage.h"
#include "Core/Graphic/Renderer/Rasterizer.h"

bool RasterizationStage::Execute(PipelineContex *ctx) {
	auto &verts = ctx->_vertexes;
	auto &indexes = ctx->_indexes;
	auto vc = verts.size();
	auto ic = indexes.size();
	for (int i = 0; i < ic - 2; i+=3) {
		if (indexes[i] < vc && indexes[i + 1] < vc && indexes[i + 2] < vc) {
			auto& v1 = verts[indexes[i]];
			auto& v2 = verts[indexes[i + 1]];
			auto& v3 = verts[indexes[i + 2]];
			Rasterizer::Rasterize(v1, v2, v3, ctx->_fragments);
		}
	}
	return true;
}

