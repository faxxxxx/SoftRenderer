#include "Rasterizer.h"
#include <math.h>



class ScanLine {
 public:
	void ToVertexs(std::vector<Fragment> &outVec) {
        if (_left.pos.x < _right.pos.x)
        {
            int fx = FloatCoord2IntLow(_left.pos.x);
            int tx = FloatCoord2IntHigh(_right.pos.x);
            int w = tx - fx;
            for (int x = fx; x <= tx; x++) {
                outVec.push_back(Lerp(_left, _right, fabs(float(x - fx) / w)));
            }
        }
        else
        {
            int fx = FloatCoord2IntLow(_right.pos.x);
            int tx = FloatCoord2IntHigh(_left.pos.x);
            int w = tx - fx;
            for (int x = fx; x <= tx; x++) {
                outVec.push_back(Lerp(_right, _left, fabs(float(x - fx) / w)));
            }
        }
	}

	Vertex _left;
	Vertex _right;
};

void Rasterizer::RasterizeHorizon(const Vertex & p1, const Vertex & p2, const Vertex & p3, std::vector<Fragment> &outVec) {
	Vertex pp1;
	Vertex pp2;
	Vertex pp3;
	if (FloatEqual(p1.pos.y, p2.pos.y)) {
		pp2 = p1;
		pp3 = p2;
		pp1 = p3;
	} else if (FloatEqual(p2.pos.y, p3.pos.y)) {
		pp2 = p2;
		pp3 = p3;
		pp1 = p1;
	} else if (FloatEqual(p1.pos.y, p3.pos.y)) {
		pp2 = p1;
		pp3 = p3;
		pp1 = p2;
	}

	float miny = pp1.pos.y;
	float maxy = pp2.pos.y;
	if (maxy < miny) {
		std::swap(miny, maxy);
	}
    
    int miny_int = FloatCoord2IntLow(miny);
    int maxy_int = FloatCoord2IntHigh(maxy);
	int h = maxy_int - miny_int;
	for (int i = miny_int; i <= maxy_int; i++) {
		ScanLine line;
		line._left = Lerp(pp2, pp1, float(i - miny_int) / h);
//        line._left.pos.y = i;
		line._right = Lerp(pp3, pp1, float(i - miny_int) / h);
//        line._right.pos.y = i;
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
