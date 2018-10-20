#pragma once
#include "Core/Base/BaseType.h"
#include <vector>

class Rasterizer {
 public:
	static void RasterizeHorizon(const Vertex& p1, const Vertex& p2, const Vertex& p3, std::vector<Vertex> &outVec);
	static void Rasterize(const Vertex& p1, const Vertex& p2, const Vertex& p3, std::vector<Vertex> &outVec);
};