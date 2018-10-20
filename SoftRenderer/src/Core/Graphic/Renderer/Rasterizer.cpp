#include "Rasterizer.h"

class ScanLine {
 public:
	void ToVertexs(std::vector<Fragment> &outVec) {
		int fx = _left.pos.x;
		int tx = _right.pos.x;
		int w = tx - fx;
		int delta = tx > fx ? 1 : -1;
		for (int x = fx; x != tx; x += delta) {
			outVec.push_back(Lerp(_left, _right, abs(float(x - fx) / w)));
		}
	}

	Vertex _left;
	Vertex _right;
};

void Rasterizer::RasterizeHorizon(const Vertex & p1, const Vertex & p2, const Vertex & p3, std::vector<Fragment> &outVec) {
	Vertex pp1;
	Vertex pp2;
	Vertex pp3;
	if (p1.pos.y == p2.pos.y) {
		pp2 = p1;
		pp3 = p2;
		pp1 = p3;
	} else if (p2.pos.y == p3.pos.y) {
		pp2 = p2;
		pp3 = p3;
		pp1 = p1;
	} else if (p1.pos.y == p3.pos.y) {
		pp2 = p1;
		pp3 = p3;
		pp1 = p2;
	}

	float miny = pp1.pos.y;
	float maxy = pp2.pos.y;
	if (maxy < miny) {
		std::swap(miny, maxy);
	}
	int h = maxy - miny;
	for (int i = (int)miny; i < (int)maxy; i++) {
		ScanLine line;
		line._left = Lerp(p2, p1, float(i - miny) / h);
		line._right = Lerp(p3, p1, float(i - miny) / h);
		line.ToVertexs(outVec);
	}
}

float PercentageFromY(const Vertex& p1, const Vertex& p2, const Vertex& p3) {
	return abs((p1.pos.y - p2.pos.y) / (p3.pos.y - p2.pos.y));
}

void Swap(Vertex &v1, Vertex &v2) {
	Vertex tmp = v1;
	v1 = v2;
	v2 = tmp;
}

void Rasterizer::Rasterize(const Vertex& p1, const Vertex& p2, const Vertex& p3, std::vector<Fragment> &outVec) {
	if (p1.pos.y == p2.pos.y
	    || p2.pos.y == p3.pos.y
	    || p1.pos.y == p3.pos.y) {
		RasterizeHorizon(p1, p2, p3, outVec);
	} else {
		Vertex vMin = p1;
		Vertex vMiddle = p2;
		Vertex vMax = p3;

		if (vMin.pos.y > vMiddle.pos.y)
			Swap(vMin, vMiddle);
		if (vMiddle.pos.y > vMax.pos.y)
			Swap(vMiddle, vMax);
		if (vMin.pos.y > vMiddle.pos.y)
			Swap(vMin, vMiddle);

		auto p4 = Lerp(vMin, vMax, PercentageFromY(vMiddle, vMin, vMax));
		RasterizeHorizon(vMin, vMiddle, p4, outVec);
		RasterizeHorizon(vMax, vMiddle, p4, outVec);
	}
}