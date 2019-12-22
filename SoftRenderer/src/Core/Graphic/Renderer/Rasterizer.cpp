#include "Rasterizer.h"
#include <math.h>
#include <assert.h>



class ScanLine {
 public:
	void ToVertexs(std::vector<Fragment> &outVec) {
<<<<<<< HEAD
        const Vertex* pLeft = &_left;
        const Vertex* pRight = &_right;
        if (_left.pos.x > _right.pos.x)
        {
            pLeft = &_right;
            pRight = &_left;
        }
        
        int fx = FloatCoord2IntLow(pLeft->pos.x);
        int tx = FloatCoord2IntHigh(pRight->pos.x);
        int w = tx - fx;
        for (int x = 0; x <= w; x++) {
            auto v = Lerp(*pLeft, *pRight, float(x) / w);
            v.pos.y = pLeft->pos.y;
            v.pos.x = fx + x;
            outVec.push_back(v);
        }
=======
		if (_left.pos.x < _right.pos.x) {
			int fx = FloatCoord2IntLow(_left.pos.x);
			int tx = FloatCoord2IntHigh(_right.pos.x);
			int w = tx - fx;
			for (int x = fx; x <= tx; x++) {
				outVec.push_back(Lerp(_left, _right, fabs(float(x - fx) / w)));
			}
		} else {
			int fx = FloatCoord2IntLow(_right.pos.x);
			int tx = FloatCoord2IntHigh(_left.pos.x);
			int w = tx - fx;
			for (int x = fx; x <= tx; x++) {
				outVec.push_back(Lerp(_right, _left, fabs(float(x - fx) / w)));
			}
		}
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
	}

	Vertex _left;
	Vertex _right;
};

void Rasterizer::RasterizeHorizon(const Vertex & p1, const Vertex & p2, const Vertex & p3, std::vector<Fragment> &outVec) {
	const Vertex* pp1 = nullptr;
	const Vertex* pp2 = nullptr;
	const Vertex* pp3 = nullptr;
	if (FloatEqual(p1.pos.y, p2.pos.y)) {
		pp2 = &p1;
		pp3 = &p2;
		pp1 = &p3;
	} else if (FloatEqual(p2.pos.y, p3.pos.y)) {
		pp2 = &p2;
		pp3 = &p3;
		pp1 = &p1;
	} else if (FloatEqual(p1.pos.y, p3.pos.y)) {
<<<<<<< HEAD
		pp2 = &p1;
		pp3 = &p3;
		pp1 = &p2;
=======
		pp2 = p1;
		pp3 = p3;
		pp1 = p2;
	} else {
		assert(false);
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
	}

    if (pp1 == nullptr ||
        pp2 == nullptr ||
        pp3 == nullptr)
        return;
    
	float miny = pp1->pos.y;
	float maxy = pp2->pos.y;
    bool swap = false;
	if (maxy < miny) {
		std::swap(miny, maxy);
        swap = true;
	}

	int miny_int = FloatCoord2IntLow(miny);
	int maxy_int = FloatCoord2IntHigh(maxy);
	int h = maxy_int - miny_int;
	AssertNotZero(h);
	for (int i = miny_int; i <= maxy_int; i++) {
		ScanLine line;
<<<<<<< HEAD
        auto per = float(i - miny_int) / h;
        if (!swap)
            line._left = Lerp(*pp1, *pp2, per);
        else
            line._left = Lerp(*pp2, *pp1, per);
        line._left.pos.y = i;
        if (!swap)
            line._right = Lerp(*pp1, *pp3, per);
        else
            line._right = Lerp(*pp3, *pp1, per);
        line._right.pos.y = i;
=======
		line._left = Lerp(pp2, pp1, float(i - miny_int) / h);
//        line._left.pos.y = i;
		line._right = Lerp(pp3, pp1, float(i - miny_int) / h);
//        line._right.pos.y = i;

>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
		line.ToVertexs(outVec);
	}
}

float PercentageFromY(const Vertex& p1, const Vertex& p2, const Vertex& p3) {
	AssertNotZero(p3.pos.y - p2.pos.y);
	return abs((p1.pos.y - p2.pos.y) / (p3.pos.y - p2.pos.y));
}

void Swap(Vertex &v1, Vertex &v2) {
	Vertex tmp = v1;
	v1 = v2;
	v2 = tmp;
}

void Rasterizer::Rasterize(const Vertex& p1, const Vertex& p2, const Vertex& p3, std::vector<Fragment> &outVec) {
	if (FloatEqual(p1.pos.y, p2.pos.y)
	    || FloatEqual(p2.pos.y, p3.pos.y)
	    || FloatEqual(p1.pos.y, p3.pos.y)) {
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
<<<<<<< HEAD
        p4.pos.y = vMiddle.pos.y;
=======
		p4.pos.y = vMiddle.pos.y;
>>>>>>> b7b5aad2bc36670a6d5a09fc7a81964ff5befb55
		RasterizeHorizon(vMin, vMiddle, p4, outVec);
		RasterizeHorizon(vMax, vMiddle, p4, outVec);
	}
}

void Rasterizer::RasterizeLine(const Vector2f &from, const Vector2f &to, const Color &c, std::vector<Fragment> &outVec) {
	int fx = (int)from.x;
	int fy = (int)from.y;
	int tx = (int)to.x;
	int ty = (int)to.y;

	int dx = tx - fx;
	int dy = ty - fy;
	float k = 0.0f;
	bool inverse = false;

	if (abs(dx) > FLT_MIN) {
		k = (float)dy / dx;
	}

	if (fabs(k) > 1 || fabs(dx) <= FLT_MIN) {
		std::swap(fx, fy);
		std::swap(tx, ty);
		std::swap(dx, dy);
		k = (float)dy / dx;
		inverse = true;
	}

	if (fx > tx) {
		std::swap(fx, tx);
		std::swap(fy, ty);
		dx = -dx;
		dy = -dy;
	}

	float e = 0.0f;
	int x = fx;
	int y = fy;
	bool iterate = (abs(k) > FLT_MIN);
	for (int i = 0; i < dx; i++) {
		if (!inverse)
			outVec.push_back(Fragment(Vector3f(x, y, 0.0f), c));
		else
			outVec.push_back(Fragment(Vector3f(y, x, 0.0f), c));
		x++;
		if (iterate) {
			e += k;
			if (k > 0) {
				if (e >= 0) {
					y++;
					e -= 1;
				}
			} else {
				if (e <= 0) {
					y--;
					e += 1;
				}
			}
		}
	}

}
